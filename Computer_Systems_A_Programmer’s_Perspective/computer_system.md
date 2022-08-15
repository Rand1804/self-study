# C语言拾遗

C和指针

### 编译过程

**预处理器(preprocessor)处理**。在这个阶段，预处理器在源代码上执行一些文本操作。例如，用实际值代替由#define 指令定义的符号以及读入由#include指令包含的文件的内容。

然后，源代码经过**解析**(parse)，判断它的语句的意思。第 2 个阶段是产生绝大

### 二进制编码

##### |， &， !， ^

或：两个中一个为1，则结果为1

与：两个都为1才是1，否则为0

非：取反 

异或：两个不同为1，相同为0

##### ||, &&

或：两个一个为真，则结果为真

与：两个都为真，结果才为真

##### <<, >>

移位运算

左移 << 超出的高位直接丢弃，低位补零

右移 >> ：分为**逻辑右移**和**算术右移**

- 逻辑右移：和左移一样，超出的低位直接丢弃，高位补0
- 算术右移：超出的低位直接丢弃，高位根据原来的符合位决定补1或0（与负数在机器中的表示形式有关）

##### 补码

Unsigned（无符号数）

$ B2U(X) = \sum\limits_{i=0}^{w-1}x_i\cdot2^i $

two's complement(补码)

$ B2T(X) = -x_{w-1}\cdot2^{w-1} + \sum\limits_{i=0}^{w-2}x_i\cdot2^i $

$-x_{w-1}\cdot2^{w-1}$为sign bit 符号位

- Unsigned Values
  - $UMin = 0$	(0000)
  - $ UMax = 2^w-1 $ (1111)   = 15
- Two's Complement Values
  - $ TMin = -2^{w-1} $      (1000) =  -8
  - $ TMax = 2^{w-1}-1 $        (0111)  = 7

##### U2T 转换

**有无符号数运算：**如果两个数都是有符号数（signed），那么会把他当作有符号数计算。如果其中任何一个无符号，那么会把另一个转换为无符号数并进行操作

> 运算中有无符号数参与的，结果都为无符号数

##### 符号位扩展

0110  -> 00110    正数直接在前面添加0，结果不变

1110 -> ==1==**1**110      负数在前面添加1，值依然不变，因为新添的1相当于-16，但是原来的符号位-8，改为了正8，他们的和依然是-8.

##### 位数缩短

**无符号数**     11011    27 -> 1011   11     变成4位相当于module16    $2^4$

**有符号数**      ~~11011   -5   ->   1011  -5      去1和符号位扩展原理一致~~

​					10011    -13  ->    0011   3       先将其当作无符号数U，也就是19，像无符号数一样取mod16，得到结果后再转回有符号数

# Chapter 2

### 二进制运算

##### **无符号数溢出**

1101 + 0101   ->    **1** 0010     2   相当于18取mod16

##### **补码溢出**

1101 + 0101    —>   **1** 0010    2    正负相加截断之后的结果反而是对的

- **负溢出**

1101 +  1010   —>   **1** 0111    7    应该的结果为-9

- **正溢出**(positive overflow)

0111 + 0101   —>   1100      -4     应该为12

乘法溢出

3×5

乘以常数

3个周期

除法30个周期

$2^{10}近似10^3$

##### 浮点数

```mermaid
graph LR
A[sign]-->B[exp]-->C[frac]
D[0]-->F[0110]-->G[111]
```

- 非规格化值

阶码:`E=1-Bias`

尾数:`M=1+f`

- 规格化值

阶码:`E=e-Bias`

尾数:`M=f`

> 其中,e是无符号数,Bias是一个等于$2^{k-1}-1$
>
> Bias值设置原因:Bias值设置主要考虑规格化值与非规格化值,也就是0000到1110,0-14,为了使他取值范围中间为0,减去偏移值7,这样就可以表示负数与非负数.为什么不用有符号数?为了统一浮点数和整数比大小

- 特殊值

阶码:全为1

- frac全为0,表示无穷
- frac非零,表示NaN

![image-20220705173851893](computer_system.assets/image-20220705173851893.png)

##### tips

关于逻辑电路:

- 只有所有位全为1的数取反为0(一般用来排除-1)
- !!(x)    x为0则为0,x非零则为1
- 一个数只有异或他本身才为0(用于 == )
- 补码取负数为~x+1(注Tmin取负为其本身)

# Chapter 3

```bash
gcc -Og -S mstore.c
# cause GCC to run the compiler,generating an assembly  file mstore.s
gcc -Og -c mstore.c
# GCC will both compile and assemble the code,generating an object-code file mstore.o that is in binary format and hence cannot be viewed directly.
objdump -d mstore.o
# disassemblers
```



## 3.4 **Accessing Information**

#### general-purpose registers

![image-20220713143716643](computer_system.assets/image-20220713143716643.png)

| 名称 | 作用                   |
| ---- | ---------------------- |
| %rdi | 第一个参数寄存器       |
| %rsi | 第二个参数寄存器       |
| %rsp | 栈顶指针               |
| %rip | 当前正在执行指令的地址 |
| %rax | 函数返回值             |



#### Operand

![image-20220714144101118](computer_system.assets/image-20220714144101118.png)

> just for sort of the sake of convenience for the hardware designers,it doesm't let you directly copy from one memory location to another.

#### ![image-20220713143649310](computer_system.assets/image-20220713143649310.png)

#### **3.4.4**  Pushing and Popping Stack Data

 the top element of the stack has the lowest address of

all stack elements

## **3.5** **Arithmetic and Logical Operations**

![image-20220713172321407](computer_system.assets/image-20220713172321407.png)

![image-20220714114353380](computer_system.assets/image-20220714114353380.png)

## 3.6 Control

![image-20220714131132974](computer_system.assets/image-20220714131132974.png)

**CF:** Carry flflag. The most recent operation generated a carry out of the most

signifificant bit. Used to detect overflflow for unsigned operations.

**ZF:** Zero flflag. The most recent operation yielded zero.

**SF:** Sign flflag. The most recent operation yielded a negative value.

**OF:** Overflflow flflag. The most recent operation caused a two’s-complement

overflflow—either negative or positive.

![image-20220714172605181](computer_system.assets/image-20220714172605181.png)

![image-20220714172908983](computer_system.assets/image-20220714172908983.png)

![image-20220718092459274](computer_system.assets/image-20220718092459274.png)

## 3.7 procedures

![image-20220719175800564](computer_system.assets/image-20220719175800564.png)

![image-20220720104719817](computer_system.assets/image-20220720104719817.png)

![image-20220721132139932](computer_system.assets/image-20220721132139932.png)

### call

- 栈顶指针 - 8
- 将此调用之后的指令地址写入栈顶部
- 跳转到目标函数的起始地址

### ret

- 读取

**integers or pointers**

![image-20220720110254808](computer_system.assets/image-20220720110254808.png)

![image-20220720150342404](computer_system.assets/image-20220720150342404.png)

![image-20220721151134044](computer_system.assets/image-20220721151134044.png)

![image-20220722142734773](computer_system.assets/image-20220722142734773.png)

| 指令           | 说明                   |
| -------------- | ---------------------- |
| break          | 打断点                 |
| run            | 运行                   |
| finish         | 运行直到当前代码块结束 |
| info registers | 显示寄存器信息         |
| print $rsp     | 输出栈指针             |
| stepi          | 逐个指令               |
| layout asm     | 布局汇编(图形界面_     |

![image-20220722165059049](computer_system.assets/image-20220722165059049.png)

![image-20220727172929243](computer_system.assets/image-20220727172929243.png)

![image-20220728164342248](computer_system.assets/image-20220728164342248.png)

> **目前64位机器会限制只使用47位的地址**

**what that means is if you tried to access any memory via the stack pointer, that was outside of the range of this 8 megabyte range you'd get a segmentation fault**

### three protections

- to randomize the stack position
- to make the stack not exectable
- use a stack canary or other mechanisms to detect a potential buffer overflow

![image-20220801130840048](computer_system.assets/image-20220801130840048.png)

![image-20220801131637554](computer_system.assets/image-20220801131637554.png)

![image-20220801132739934](computer_system.assets/image-20220801132739934.png)

![image-20220801134302284](computer_system.assets/image-20220801134302284.png)

# Chapter 4

![image-20220802170717676](computer_system.assets/image-20220802170717676.png)

![image-20220802171320954](computer_system.assets/image-20220802171320954.png)

![image-20220802171350006](computer_system.assets/image-20220802171350006.png)

![image-20220802174839875](computer_system.assets/image-20220802174839875.png)

![image-20220802110326631](computer_system.assets/image-20220802110326631.png)

![image-20220803114505539](computer_system.assets/image-20220803114505539.png)

![image-20220803114518921](computer_system.assets/image-20220803114518921.png)

![image-20220803115637868](computer_system.assets/image-20220803115637868.png)

![image-20220803115800472](computer_system.assets/image-20220803115800472.png)

![image-20220803133809677](computer_system.assets/image-20220803133809677.png)

![image-20220803134056708](computer_system.assets/image-20220803134056708.png)

![image-20220803153039950](computer_system.assets/image-20220803153039950.png)

![image-20220803154226336](computer_system.assets/image-20220803154226336.png)

# Chapter 5

- 减少不必要的函数调用
- 消除不必要的内存引用
- 多路并行循环展开
- 重新结合变换

![image-20220804172428824](computer_system.assets/image-20220804172428824.png)

# Chapter 6

![image-20220808100927441](computer_system.assets/image-20220808100927441.png)

## Random Access Memory(随机访问存储器)

- Static RAM(静态RAM, SRAM)   ------- Cache memory
  - 每个bit位的信息存储在一个**双稳态**的存储单元内,每个存储单眼需要六个晶体管来实现
- Dynamic RAM(动态RAM, DRAM) --------- Main memory/ frame buffers
  - 每个bit位的存储对应一个**电容**和一个晶体管

![image-20220808105726131](computer_system.assets/image-20220808105726131.png)

>  二维阵列减少了地址引脚数量,增加了访问时间

![image-20220808110207946](computer_system.assets/image-20220808110207946.png)

### DDR3,DDR4,LPDDR4

DDR SDRM - Double Data-Rate Synchronous DRAM (双倍速率同步动态随机存储器)

DDR4 --------> 预取缓冲区16bit

DDR4 ---------> 预取缓冲区8bit

LP -------------> Low Power

## Disk 

- 机械磁盘(也称旋转磁盘)

![image-20220808111955274](computer_system.assets/image-20220808111955274.png)

![image-20220808112049168](computer_system.assets/image-20220808112049168.png)

![image-20220808112203938](computer_system.assets/image-20220808112203938.png)

![image-20220808113405499](computer_system.assets/image-20220808113405499.png)

![image-20220808113750218](computer_system.assets/image-20220808113750218.png)

## Solid State Disk

![image-20220808114042923](computer_system.assets/image-20220808114042923.png)

![image-20220808135313564](computer_system.assets/image-20220808135313564.png)

![image-20220808135539081](computer_system.assets/image-20220808135539081.png)

![image-20220808140052504](computer_system.assets/image-20220808140052504.png)

![image-20220808140552521](computer_system.assets/image-20220808140552521.png)

## Locality

### temporal locality

时间局部性

### spatial locality

空间局部性

![image-20220810101534088](computer_system.assets/image-20220810101534088.png)

![image-20220808152824617](computer_system.assets/image-20220808152824617.png)

![image-20220810101735719](computer_system.assets/image-20220810101735719.png)

### 缓存是否命中确认

- (1) set selection(组选择)
- (2) line matching(行匹配)
- (3) word extraction(字抽取)

![image-20220810103825072](computer_system.assets/image-20220810103825072.png)

### Issues with Writes

- Write Hit(写命中)
  - write-through(写穿透)
  - write-back(写回)
- Write Miss(写不命中)
  - write-allocate(写分配) :先把目标数据所在的块从内存(更低一级cache)加载到cache中,然后再往cache中写
  - no-write-allocate(写不分配) :绕开cache,直接把要写的内容写到内存(更低一级cache)中

通常情况下写分配与写回,写不分配与写穿透搭配使用

![image-20220810133323812](computer_system.assets/image-20220810133323812.png)