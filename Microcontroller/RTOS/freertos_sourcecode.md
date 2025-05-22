


## task.c


pxTCB->xGenericListItem  一共有4种可能的链表。xSuspendedTaskList， pxReadyTasksLists， pxDelayedTaskList， pxOverflowDelayedTaskList
pxTCB->xEventListItem 只可能在`xPendingReadyList`中， 在`xTaskResume`中任务调度关闭时被添加，在`xTaskResumeAll`中被全部删除并加入readylist


1. 新加入的任务添加到`readytasklist`对应优先级索引的最后
2. taskYIELD 触发pendSV中断来进行一次任务切换
3. 具体任务调度过程：首先由`vTaskStartScheduler`创建一个空闲任务（在`xTaskCreate`初次调用时会初始化所有`pxReadyTasksLists`，以及其他任务相关初始化），然后设置PSP为零，触发`PendSV`中断，开始第一个任务。`xPortPendSVHandler`处理`PendSV`中断，如果PSP为0，则跳过保存寄存器步骤，直接调用`vTaskSwitchContext`,该函数找到非空的最高优先级的ready队列，将`pxCurrentTCB`赋值为`pxIndex`指向的TCB。然后`PendSV`中断从TCB中获取目标任务的栈顶指针，将寄存器恢复为保存在栈中的值。获取中断屏蔽计数（因为在每次`yeild`开始时都打开中断，所以才能进入该`PendSV`中断）,如果计数为0，则打开中断，然后返回r14的值的地址
4. 时间管理：调用systick中断处理程序`xPortSysTickHandler`，关闭中断，调用`vTaskIncrementTick`,如果任务调度被暂停，则增加`uxMissedTicks`计数。如果没有暂停，则增加`xTickCount`计数，然后检查`pxDelayedTaskList`,拿出第一个节（因为该链表是从小到大排序的，`pxTCB->xGenericListItem->xItemValue`存储了该任务的延迟时间，将该任务从延迟队列中移除，如果它也存在于事件队列中，也一并移除。然后加入`pxReadyTasksLists`。如果开启了抢占式调用`configUSE_PREEMPTION`,则调用一次`vPortYieldFromISR`进行上下文切换。退出前检查`uxCriticalNesting`计数，以恢复到调用`vPortYieldFromISR`之前的中断屏蔽状态
5. `vTaskDelay`: 如果需要延迟的ticks等于0，则相当于进行一次任务调度。如果大于0，首先将该任务从readylist中移除，然后将该任务TCB中genericitem中的值设置为将要唤醒的时间。如果将要唤醒的ticks小于当前的ticks，则说明溢出了，将该任务加入溢出延迟任务链表，否则加入延迟任务链表。最后恢复任务调度。
6. `xTaskResumeAll`: 将`uxSchedulerSuspended`计数减一，如果为0，则当前任务调度为打开状态，然后将`xPendingReadyList`中的所有任务从事件链表和通用链表中移除，加入准备链表，如果我们刚才操作的任务优先级大于当前运行任务的优先级，则设置需要调度。如果在调度阻塞期间有任何ticks发生，则循环调用`vTaskIncrementTick`，并且`uxMissedTicks`减一，直到为0。
7. `vTaskSuspend`: 挂起某个任务，首先判断传入的参数是否为NULL，如果为NULL则说明需要挂起当前任务，不为NULL则挂起目标任务。挂起的过程为先通过`pxTCB->xGenericListItem->pvContainer`获取目标任务在哪个队列里（延迟或者准备队列），然后将其删除，并且如果他也在事件链表中，也一并删除，最后将`pxTCB->xGenericListItem`插入**挂起链表**中的`pxTCB->xGenericListItem->pxIndex`之后。如果被挂起的是当前任务，则进行一次任务调度。
8. `vTaskResume`: 恢复某个任务。首先判断当前调度器是否开启，如果开启，则将该任务`xGenericListItem`从当前所在的队列中移除，加入准备链表，并且如果优先级比当前任务优先级高，则进行一次任务调度。如果任务调度器当前是关闭状态，则将其`xEventListItem`插入`xPendingReadyList`事件链表。



## queue.c


### `prvUnlockQueue`
队列发送和接收锁计数减一，如果减一之后依然大于-1，则说明在队列锁住的时候，有从中断中操作过队列，添加或减少数据。将锁置为-1，然后将队列结构中的头部等待移除，加入准备任务队列。如果任务调度被暂停，则加入代表准备任务事件链表

### `xQueueCreate`
初始化队列。首先给队列结构本身分配空间，然后给存储区分配需求字节+1字节（作为队尾标志，使用环形缓冲来实现元素存储），然后初始化队列结构体，包括读写索引，等待读或写任务链表等。

### `xQueueSend`
停止任务调度，将任务列表锁住标志置位（仅阻止中断访问事件链表）。如果队列满了，且可以等待，则将任务加入等待队列`xTasksWaitingToSend`，该任务可以被两种情况唤醒。1.超时 2. 队列里有空位了。然后关闭中断，解锁队列，释放控制权，进入阻塞。当再次被唤醒时，说明队列中出现了空位或者超时。然后恢复任务调度关闭和队列锁住状态。屏蔽中断，判断当前队列是否满，如果满返回错误，非满则将数据复制到队列中，并且将发送队列锁加1，解除中断屏蔽。接下来就是退出处理，解锁队列锁，并且恢复任务调度

### `xQueueSendFromISR`
1. 如果当前队列还有空位，则将数据移入，
    1. 如果当前队列发送没锁，且该中断中之前没有任务已经唤醒，则将处于接收事件队列头部的任务移动到准备队列中
    2. 如果当前队列发送被锁，则仅将发送锁加1
2. 什么都不做，直接返回



 `xTaskPreviouslyWoken` is a flag used to coordinate task waking across multiple ISR operations. Let me explain its purpose:

1. Purpose of the Flag:
```c
signed portBASE_TYPE xTaskPreviouslyWoken // Input parameter indicating if a task was already woken
```
- Indicates if a higher priority task was already woken by another operation in the same ISR
- Used to optimize context switching decisions
- Shared across multiple ISR operations

2. How it's used in the code:
```c
if( !xTaskPreviouslyWoken )  // Only check for tasks to wake if none woken yet    
{
    if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
    {
        if( xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != pdFALSE )
        {
            return pdTRUE;  // Indicates a higher priority task was woken
        }
    }
}
```

3. Typical Usage Pattern:
```c
void ISR_Handler(void)
{
    signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    // First queue operation
    xHigherPriorityTaskWoken = xQueueSendFromISR(queue1, &data1, xHigherPriorityTaskWoken);

    // Second queue operation
    xHigherPriorityTaskWoken = xQueueSendFromISR(queue2, &data2, xHigherPriorityTaskWoken);

    // If any operation woke a higher priority task, request context switch
    if(xHigherPriorityTaskWoken)
    {
        // Trigger context switch
        portYIELD_FROM_ISR();
    }
}
```

The key points about `xTaskPreviouslyWoken`:
1. It's shared across multiple ISR operations
2. Once TRUE, stays TRUE for the rest of the ISR
3. Used to decide if context switch is needed after ISR
4. Helps optimize by preventing unnecessary task checks
5. Ensures only one high-priority task wake-up is processed


### `xQueueReceive`
标识位`xRxLock`：
1. 在`xQueueReceive`中读取数据之后加1
2. 在`prvUnlockQueue`中减1，之后并判断是否大于-1，如果大于-1则赋值为-1，然后唤醒一个在`xTasksWaitingToSend`中的头任务
3. `xQueueReceiveFromISR`有空位且队列当前被锁，则仅将`xRxLock`标识位加1
标识位`xTxLock`：
1. 在`xQueueSend`中写入数据之后加1
2. 在`prvUnlockQueue`中减1，之后并判断是否大于-1，如果大于-1则赋值为-1，然后唤醒一个在`xTasksWaitingToSend`中的头任务
3. `xQueueReceiveFromISR`有空位且队列当前被锁，则仅将`xRxLock`标识位加1

1. 关闭任务调度，锁住队列，判断队列是否为空。
	1. 如果为空，则判断是否等待
		1. 如果等待，则将当前任务的事件元素加入队列等待接收链表。屏蔽中断，解锁队列，恢复调度，然后触发一次`PendSV`中断。被唤醒后恢复之前的状态，停止调度，锁住队列，退出屏蔽中断。
	主流程：屏蔽中断，判断队列中元素是否大于0，如果大于0，则读出一个元素，接收锁计数加1。
	最后做一些退出前的恢复工作，取消中断屏蔽，解锁队列，恢复任务调度，根据需要决定是否触发`PendSV`中断
