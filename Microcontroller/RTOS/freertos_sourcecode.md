


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

`xQueueCreate`: 初始化队列。首先给队列结构本身分配空间，然后给存储区分配需求字节+1字节（作为队尾标志，使用环形缓冲来实现元素存储），然后初始化队列结构体，包括读写索引，等待读或写任务链表等。

`xQueueSend`: 停止任务调度，将任务列表锁住标志置位，不让中断获取。判断队列是否满了，以及是否等待