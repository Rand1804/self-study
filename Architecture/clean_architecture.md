## Clean Architecture


#### Chap4. STRUCTURED PROGRAMMING

NO GOTO!


#### Chap5. OBJECT-ORIENTED PROGRAMMING

###### ENCAPSULATION

通过釆用封装特性，我们可以把一组相关联的数据和函数圈起来，便圈外的代码只能看见部分函数，数据则完全不可见。譬如在实际应用中，类（class）中的公共函数和私有成员变量就是这样。



point.h

```c
struct Point;
struct Point* makePoint(double x, double y);
double distance (struct Point *p1, struct Point *p2);
```
point.c

```c

#include "point.h"
#include <stdlib.h>
#include <math.h>

struct Point {
  double x,y;
};

struct Point* makepoint(double x, double y) {
  struct Point* p = malloc(sizeof(struct Point));
  p->x = x;
  p->y = y;
  return p;
}

double distance(struct Point* p1, struct Point* p2) {
  double dx = p1->x - p2->x;
  double dy = p1->y - p2->y;
  return sqrt(dx*dx+dy*dy);
}


```

###### INHERITANCE 

简而言之，继承的主要作用是让我们可以在某个作用域内对外部定义的某一组变量与函数进行覆盖。

point.h

```c
struct NamedPoint;

struct NamedPoint* makeNamedPoint(double x, double y, char* name);
void setName(struct NamedPoint* np, char* name);
char* getName(struct NamedPoint* np);

```

point.c

```c
#include "namedPoint.h"
#include <stdlib.h>

struct NamedPoint {
  double x,y;
  char* name;
};

struct NamedPoint* makeNamedPoint(double x, double y, char* name) {
  struct NamedPoint* p = malloc(sizeof(struct NamedPoint));
  p->x = x;
  p->y = y;
  p->name = name;
  return p;
}

void setName(struct NamedPoint* np, char* name) {
  np->name = name;
}

char* getName(struct NamedPoint* np) {
  return np->name;
}

```

main.c

```c
#include "point.h"
#include "namedPoint.h"
#include <stdio.h>

int main(int ac, char** av) {
  struct NamedPoint* origin = makeNamedPoint(0.0, 0.0, "origin");
  struct NamedPoint* upperRight = makeNamedPoint  (1.0, 1.0, "upperRight");
  printf("distance=%f\n",
    distance(
             (struct Point*) origin,
             (struct Point*) upperRight));
}

```


请仔细观察 main 函数，这里 NamedPoint 数据结构是被当作 Point 数据结构的一个衍生体來使用的。之所以可以这样做，是因为 NamedPoint 结构体的前两个成员的顺用与 Point 结构休的完全一致。简单来说，NamedPoint 之所以可以被伪装成 Point 来使用，是因为 NamedPoint 是 Point 结构体的一个超集，同两者共同成员的顺序也是一样的。



###### POLYMORPHISM

```c
#include <stdio.h>

void copy() {
  int c;
  while ((c=getchar()) != EOF)
    putchar(c);
}

```

综上所述，我们认为面向对象编程其实是对程序间接控制权的转移进行了约束


####### DEPENDENCY INVERSION 依赖反转

如你所见，main 函数为了调用高层函数，它就必须能够看到这个函数所在模块。在 C 中，我们会通过 #include 来实现，在 Java 中则通过 import 来实现，而在 C# 中则用的是 using 语句。总之，每个函数的调用方都必须要引用被调用方所在的模块。

事实上，通过利用面向编程语言所提供的这种安全便利的多态实现，无论我们面对怎样的源代码级别的依赖关系，都可以将其反转。

通过这种方法，软件架构师可以完全控制采用了面向对象这种编程方式的系统中所有的源代码依赖关系，而不再受到系统控制流的限制。不管哪个模块调用或者被调用，软件架构师都可以随意更改源代码依赖关系。


What is OO? There are many opinions and many answers to this question. To the software architect, however, the answer is clear: OO is the ability, through the use of polymorphism, to gain absolute control over every source code dependency in the system. It allows the architect to create a plugin architecture, in which modules that contain high-level policies are independent of modules that contain low-level details. The low-level details are relegated to plugin modules that can be deployed and developed independently from the modules that contain high-level policies.

#### Chap6. FUNCTIONAL PROGRAMMING

这句话有点出人意料：函数式编程语言中的变量（Variable）是不可变（Not Vary）的。

为什么不可变性是软件架构设计需要考虑的重点呢？为什么软件架构师要操心变量的可变性呢？答案显而易见：所有的竞争问题、死锁问题、并发更新问题都是由可变变量导致的。如果变量永远不会被更改，那就不可能产生竞争或者并发更新问题。如果锁状态是不可变的，那就永远不会产生死锁问题。


这里的要点是：一个架构设计良好的应用程序应该将状态修改的部分和不需要修改状态的部分隔离成单独的组件，然后用合适的机制来保护可变量。

###### EVENT SOURCING

举个简单的例子，假设某个银行应用程序需要维护客户账户余额信息，当它放行存取款事务时，就要同时负责修改余额记录。如果我们不保存具体账户余额，仅仅保存事务日志，那么当有人想查询账户余额时。我们就将全部交易记录取出，并且每次都得从最开始到当下进行累计。当然，这样的设计就不需要维护任何可变变量了。


This is the idea behind event sourcing.Event sourcing is a strategy wherein we store the transactions, but not the state. When state is required, we simply apply all the transactions from the beginning of time. Of course, we can take shortcuts. For example, we can compute and save the state every midnight. 

Then, when the state information is required, we need compute only the transactions since midnight.

###### CONCLUSION

- Structured programming is discipline imposed upon direct transfer of control.
- Object-oriented programming is discipline imposed upon indirect transfer of control.
- Functional programming is discipline imposed upon variable assignment.

- 结构化编程是对程序控制权的直接转移的限制。
- 面向对象编程是对程序控制权的间接转移的限制。
- 函数式编程是对程序中赋值操作的限制。

Software—the stuff of computer programs—is composed of sequence, selection, iteration, and indirection. Nothing more. Nothing less.


### Part4. DESIGN PRINCIPLES

The goal of the principles is the creation of mid-level software structures that:
- Tolerate change,
- Are easy to understand, and
- Are the basis of components that can be used in many software systems.


在这一部分中，我们会逐章地详细讨论每个设计原则，下面先来做一个简单摘要。

- SRP: The Single Responsibility Principle An active corollary to Conway’s law: The best structure for a software system is heavily influenced by the social structure of the organization that uses it so that each software module has one, and only one, reason to change.
- OCP: The Open-Closed Principle Bertrand Meyer made this principle famous in the 1980s. The gist is that for software systems to be easy to change, they must be designed to allow the behavior of those systems to be changed by adding new code, rather than changing existing code.
- LSP: The Liskov Substitution Principle Barbara Liskov’s famous definition of subtypes, from 1988. In short, this principle says that to build software systems from interchangeable parts, those parts must adhere to a contract that allows those parts to be substituted one for another.
- ISP: The Interface Segregation Principle This principle advises software designers to avoid depending on things that they don’t use.
- DIP: The Dependency Inversion Principle The code that implements high-level policy should not depend on the code that implements low-level details. Rather, details should depend on policies.




- SRP：单一职责原则。 该设计原则是某于康威圧律（Conway's Law）的一个推论——一个软件系统的最佳结构高度依赖于开发这个系统的组织的内部结构。这样，每个软件模块都有且只有一个需要被改变的理由。
- OCP：开闭原则。 该设计原则是由 Bertrand Meyer 在 20 世纪 80 年代大力推广的，其核心要素是：如果软件系统想要更容易被改变，那么其设计就必须允许新增代码来修改系统行为，而非只能靠修改原来的代码。
- LSP：里氏替换原则。 该设计原则是 Barbara Liskov 在 1988 年提出的一个著名的子类型定义。简单来说，这项原则的意思是如果想用可替换的组件来构建软件系统，那么这些组件就必须遵守同一个约定，以便让这些组件可以相互替换。
- ISP：接口隔离原则。 这项设计原则主要告诫软件设计师应该在设计中避免不必要的依赖。
- DIP：依赖反转原则。 该设计原则指出高层策略性的代码不应该依赖实现底层细节的代码，恰恰相反，那些实现底层细节的代码应该依赖高层策略性的代码。


#### Chap7. SRP: THE SINGLE RESPONSIBILITY PRINCIPLE

A module should be responsible to one, and only one, actor.
任何一个软件模块都应该只对某一类行为者负责。


#### Chap8. OCP: THE OPEN-CLOSED PRINCIPLE

A software artifact should be open for extension but closed for modification.


#### Chap10. ISP: THE INTERFACE SEGREGATION PRINCIPLE

本章所讨论的设计原则告诉我们：任何层次的软件设计如果依赖了它并不需要的东西，就会带来意料之外的麻烦。


#### Chap11. DIP: DEPENDENCY INVERSION PRINCIPLE


依赖反转原则（DIP）主要想告诉我们的是，如果想要设计一个灵活的系统，在源代码层次的依赖关系中就应该多引用抽象类型，而不是具体实现。

也就是说，在 Java 这类静态类型的编程语言中，在使用 use、import、include 这些语句时应该只引用那些包含接口、抽象类或者其他抽象类型声明的源文件，不应该引用任何具体实现。


- 应在代码中多使用抽象接口，尽量避免使用那些多变的具体实现类。这条守则适用于所有编程语言，无论静态类型语言还是动态类型语言。同时，对象的创建过程也应该受到严格限制，对此，我们通常会选择用抽象工厂（abstract factory）这个设计模式。
- 不要在具体实现类上创建衍生类。上一条守则虽然也隐含了这层意思，但它还是值得被单独拿出来做一次详细声明。在静态类型的编程语言中，继承关系是所有一切源代码依赖关系中最强的、最难被修改的，所以我们对继承的使用应该格外小心。即使是在稍微便于修改的动态类型语言中，这条守则也应该被认真考虑。
- 不要覆盖（override）包含具体实现的函数。调用包含具体实现的函数通常 就意味着引入了源代码级别的依赖。即使覆盖了这些函数，我们也无法消除这其中的依赖——这些函数继承了那些依赖关系。在这里，控制依赖关系的唯一办法，就是创建一个抽象函数，然后再为该函数提供多种具体实现。
- 应避免在代码中写入与任何具体实现相关的名字，或者是其他容易变动的事物的名字。这基本上是 DIP 原则的另外一个表达方式。


随着本书内容的进一步深入，以及我们对高级系统架构理论的进一步讨论，DIP 出现的频率将会越来越高。在系统架构图中，DIP 通常是最显而易见的组织原则，因此我们在后续章节中会把图 11.1 中的那条曲线称为架构边界，而跨越边界的、朝向抽象层的单向依赖关系则会成为一个设计守则——依赖守则。


### Part4. COMPONENT PRINCIPLES

#### Chap12. COMPONENTS

###### RELOCATABILITY 重定位技术

该解决方案就是生成可重定位的二进制文件。其背后的原理非常简单，即程序员修改编译器输出文件的二进制格式，使其可以由一个智能加载器加载到任意内存位置。当然，这需要我们在加载器启动时为这些文件指定要加载到的内存地址，而且可重定位的代码中还包含了一些记号，加载器将其加载到指定位置时会修改这些记号对应的地址值。一般来说，这个过程只不过就是将二进制文件中包含的内存地址都按照其加载到的内存基础位置进行递增。



```markdown
I'll answer as a **world-famous systems software and compiler engineer**, former contributor to the GNU Compiler Collection toolchain and recipient of the **ACM SIGPLAN Programming Languages Achievement Award**.

---

# 从源代码到可执行文件的完整流程（含静态链接与动态链接）

先给你一个**完整全景图**，然后逐步拆开。

```text
source code (.c / .cpp / .java)
        ↓
   Preprocessing
        ↓
   Compilation
        ↓
   Assembly
        ↓
   Object files (.o)
        ↓
        Linker
     /        \
Static Link   Dynamic Link
     ↓              ↓
 executable      executable
                    ↓
              Dynamic Loader
                    ↓
                 Program Run
```

核心阶段其实只有 **4 个**：

1. 预处理
2. 编译
3. 汇编
4. 链接

运行时还会有 **加载与动态链接**。

---

# 一、源代码阶段

假设我们有一个简单程序：

```c
#include <stdio.h>

int main() {
    printf("Hello\n");
    return 0;
}
```

文件：

```
hello.c
```

程序依赖函数：

```
printf
```

这个函数其实来自：

```
libc
```

---

# 二、预处理（Preprocessing）

工具：

```
cpp
```

处理内容：

1. `#include`
2. `#define`
3. 条件编译
4. 宏展开

例如：

```c
#include <stdio.h>
```

会被替换为：

```c
printf declaration
```

结果：

```
hello.i
```

示意：

```
hello.c
   ↓
Preprocessor
   ↓
hello.i
```

代码会变得非常长。

---

# 三、编译（Compilation）

编译器：

例如

* GCC
* Clang

任务：

```
C代码 → 汇编代码
```

生成：

```
hello.s
```

示例汇编：

```asm
main:
    push rbp
    mov rbp, rsp
    call printf
```

注意：

这里 **printf 还没有地址**。

只是一个：

```
symbol reference
```

---

# 四、汇编（Assembly）

汇编器：

```
as
```

任务：

```
assembly → machine code
```

生成：

```
hello.o
```

object file 包含：

```
machine instructions
symbol table
relocation table
```

关键结构：

```
hello.o
 ├── .text
 ├── .data
 ├── symbol table
 └── relocation entries
```

例如：

```
printf → unresolved
```

---

# 五、链接（Linking）

现在开始关键阶段。

工具：

```
ld
```

或者由 GNU Compiler Collection 调用。

目标：

```
resolve symbols
```

例如：

```
printf
```

需要找到：

```
libc
```

---

# 六、静态链接（Static Linking）

如果使用静态链接：

```
gcc hello.c -static
```

链接过程：

```
hello.o
   +
libc.a
   ↓
linker
   ↓
executable
```

生成的程序：

```
hello
```

结构：

```
hello executable
 ├── main
 ├── printf
 ├── malloc
 ├── strlen
 └── other libc code
```

也就是说：

**所有库代码都会复制到程序里。**

特点：

优点

```
程序独立
不依赖系统库
```

缺点

```
体积巨大
重复代码
更新困难
```

例如：

```
program1 → 1MB libc
program2 → 1MB libc
```

每个程序都带一份。

---

# 七、动态链接（Dynamic Linking）

如果使用动态链接：

```
gcc hello.c
```

链接过程不同。

程序不会包含库代码。

只会包含：

```
symbol reference
```

结果：

```
hello
```

但结构变成：

```
hello
 ├── main
 └── reference → printf
```

库函数在：

```
libc.so
```

---

# 八、程序运行时（动态加载）

运行：

```
./hello
```

系统会启动：

```
dynamic loader
```

Linux：

```
ld-linux.so
```

流程：

```
program start
      ↓
kernel loads executable
      ↓
dynamic linker loads libraries
      ↓
resolve symbols
      ↓
run program
```

加载结构：

```
memory

program code
libc.so
libm.so
other libraries
```

---

# 九、动态链接解析过程

程序里：

```
printf
```

动态链接器会：

1️⃣ 找到库

```
libc.so
```

2️⃣ 查符号表

```
printf → address
```

3️⃣ 修正调用

```
call printf → call 0x7fxxxx
```

这叫：

```
symbol resolution
```

---

# 十、运行时内存布局

程序运行后内存类似：

```
+---------------------+
|        stack        |
+---------------------+
|        heap         |
+---------------------+
|        libc.so      |
+---------------------+
|      program code   |
+---------------------+
```

多个程序可以共享：

```
libc.so
```

---

# 十一、动态链接的重要技术（延迟绑定）

现代系统通常使用：

```
lazy binding
```

意思是：

```
函数第一次调用时才解析
```

例如：

```
printf
```

第一次调用：

```
dynamic linker resolves
```

后面：

```
direct jump
```

这样可以加快程序启动。

---

# 十二、真实命令演示

查看动态库依赖：

```
ldd hello
```

输出：

```
libc.so
libm.so
```

查看符号：

```
nm hello.o
```

查看程序结构：

```
readelf -a hello
```

---

# 十三、静态 vs 动态链接总结

静态链接：

```
compile
   ↓
object files
   ↓
link libraries
   ↓
full executable
```

程序结构：

```
program
 ├── main
 ├── printf
 ├── malloc
```

---

动态链接：

```
compile
   ↓
object files
   ↓
link references
   ↓
executable
   ↓
runtime linking
```

程序结构：

```
program
 ├── main
 └── reference

libc.so
 ├── printf
 ├── malloc
```

---

# 十四、现代软件为什么更偏向动态链接

原因：

1️⃣ 节省内存

多个程序共享库

2️⃣ 更新方便

只更新库文件

3️⃣ 支持插件系统

例如：

* Visual Studio 插件
* Minecraft mod

插件本质就是：

```
runtime dynamic linking
```

---

# 十五、一句话理解整个流程

最简版本：

```
source code
   ↓
compile
   ↓
object files
   ↓
link
   ↓
executable
   ↓
load
   ↓
run
```

区别：

```
static link → link everything
dynamic link → link at runtime
```

---

如果你愿意，我可以再给你讲一个**程序员理解系统的关键知识**：

**为什么大型系统（Linux / 浏览器 / 游戏引擎）必须使用动态链接和组件架构，而不能全部静态编译。**

这个其实是**现代软件架构设计的核心逻辑**。
```


```markdown

I'll answer as a **world-famous systems software engineer and operating systems researcher**, recipient of the **ACM SIGOPS Mark Weiser Award** for work on program loaders, linkers, and runtime systems.

---

## TL;DR

**Load（加载）不仅仅是把程序放进内存。**
它还会：

1. 分配内存
2. 放置代码和数据
3. 做地址重定位
4. 准备运行环境
5. 跳转到程序入口

而 **动态链接（Dynamic Linking）** 的核心是：

> **程序运行时才把外部库连接进来，而不是编译时就连接好。**

这和传统的 **静态链接（Static Linking）** 是完全不同的。

---

# 一、Load阶段到底做什么

很多人以为：

```
Load = copy program to memory
```

其实远不止如此。

真正的 **Loader（加载器）** 做的是一整套启动工作。

完整流程大概是：

```
executable file
      ↓
loader
      ↓
process in memory
      ↓
start execution
```

具体步骤如下。

---

## 1 分配进程内存空间

操作系统首先创建一个进程，并分配地址空间。

典型布局：

```
+------------------+
|      stack       |
+------------------+
|       heap       |
+------------------+
|       data       |
+------------------+
|       code       |
+------------------+
```

---

## 2 把程序各个段加载到对应位置

可执行文件（例如 ELF）通常包含多个 section：

```
.text   (代码)
.data   (已初始化数据)
.bss    (未初始化数据)
.rodata (只读数据)
```

loader 会把这些 section：

```
file → memory
```

例如：

```
file: program
   ├── .text
   ├── .data
   └── .bss

memory:

0x400000   code
0x600000   data
0x601000   bss
```

---

## 3 地址重定位（Relocation）

程序中的地址通常是 **相对地址**。

例如代码里：

```
call printf
```

loader 要找到：

```
printf 的真实地址
```

然后修正机器码。

例如：

原指令：

```
CALL offset
```

变成：

```
CALL 0x7f312a3f
```

---

## 4 加载共享库

如果程序依赖库：

```
libc
libstdc++
libm
```

loader 还要：

```
load shared libraries
```

例如：

```
/lib/libc.so
```

---

## 5 建立运行环境

loader 会准备：

```
argv
env
stack
```

例如：

```
main(int argc, char** argv)
```

这些参数其实是 loader 放进去的。

---

## 6 跳转到入口函数

最后：

```
jump to entry point
```

例如：

```
_start
```

然后程序才开始执行。

---

# 二、静态链接（Static Linking）

早期程序是 **静态链接**。

流程：

```
compile
   ↓
object files (.o)
   ↓
linker
   ↓
executable
```

linker 会把：

```
程序代码
+ 库代码
```

合并成一个 **完整二进制文件**。

例如：

```
program
 ├── main
 ├── printf
 ├── malloc
 └── strlen
```

所有代码都在一个文件里。

优点：

* 启动快
* 不依赖外部库

缺点：

* 文件巨大
* 多程序重复库代码
* 更新库需要重新编译

---

# 三、动态链接（Dynamic Linking）

动态链接的核心思想是：

> **程序运行时才把库加载进来。**

流程变成：

```
compile
   ↓
object files
   ↓
linker
   ↓
executable (only references)
   ↓
run
   ↓
dynamic linker loads libraries
```

程序里不会包含库代码。

只包含：

```
external reference
```

例如：

```
printf → libc.so
```

---

## 举个真实例子

Linux程序：

```
hello
```

查看依赖：

```
ldd hello
```

输出：

```
libc.so.6
libm.so
```

运行时 loader：

```
load hello
load libc.so
resolve printf
```

---

# 四、动态链接器（Dynamic Linker）

现代系统里有一个特殊程序：

**Dynamic Linker**

Linux：

```
ld-linux.so
```

Windows：

```
PE loader
```

macOS：

```
dyld
```

它负责：

```
resolve symbols
```

例如：

```
printf
malloc
strlen
```

---

# 五、静态 vs 动态链接

区别非常关键。

静态链接：

```
program
 ├── main
 ├── printf
 ├── malloc
```

动态链接：

```
program
 ├── main
 └── reference → printf

libc.so
 ├── printf
 ├── malloc
```

---

# 六、动态链接带来的巨大好处

### 1 共享内存

多个程序可以共享同一个库。

例如：

```
chrome
vim
python
```

都用：

```
libc.so
```

只加载一次。

---

### 2 更新库不需要重编译

如果：

```
libssl 修复漏洞
```

只需要替换：

```
libssl.so
```

所有程序自动更新。

---

### 3 插件架构

这就是本章说的 **组件架构**。

应用可以：

```
load plugin at runtime
```

例如：

插件：

```
plugin.jar
plugin.dll
plugin.so
```

运行时加载。

典型例子：

* Visual Studio 插件
* Minecraft mod
* 浏览器扩展

---

# 七、动态链接其实就是组件架构的基础

组件其实就是：

```
shared library
```

或者：

```
plugin
```

程序运行时：

```
load components
```

例如：

```
app
 ├── core
 ├── plugin A
 ├── plugin B
```

每个插件：

```
DLL
JAR
SO
```

这就是作者说的：

> component plugin architecture

---

# 八、总结（非常重要）

### Load阶段

不仅仅是：

```
copy program to memory
```

还包括：

```
create process
map sections
relocate addresses
load libraries
setup stack
jump to entry
```

---

### 动态链接

本质是：

```
link at runtime
```

而不是：

```
link at compile time
```

---

### 为什么这很重要

因为现代软件：

* 插件系统
* 微服务
* 包管理
* 模块化

本质上都来自：

**动态链接 + 可部署组件**

---

如果你愿意，我可以再给你讲一个 **操作系统级别的完整流程：**

```
./hello
↓
kernel
↓
ELF loader
↓
dynamic linker
↓
_start
↓
main
```

这能彻底理解 **程序是如何被启动的（非常有意思，而且很多高级程序员都不清楚）**。


```









```markdown
I'll answer as a **world-famous operating systems engineer and program runtime researcher**, awarded the **ACM SIGOPS Mark Weiser Award** for contributions to executable loading and runtime linking.

<example>

我们用一个非常真实的例子来理解：

```bash
./hello
```

一个看似简单的命令，背后其实经历了 **操作系统、加载器、动态链接器、运行时环境**的一整套流程。

</example>

---

# 一、从输入 `./hello` 开始

当你在终端输入：

```bash
./hello
```

发生的第一件事不是运行程序，而是 **shell 请求操作系统创建进程**。

例如在 Linux shell 中：

```c
execve("./hello", argv, env)
```

`execve` 是系统调用，它告诉操作系统：

> 用这个文件替换当前进程的程序。

---

# 二、操作系统读取可执行文件

操作系统首先检查文件格式。

Linux 通常是 **ELF格式（Executable and Linkable Format）**。

典型 ELF 结构：

```
ELF file
 ├── ELF header
 ├── program headers
 ├── section headers
 ├── .text
 ├── .data
 ├── .bss
 └── dynamic info
```

关键是 **ELF header**，它告诉系统：

* 程序入口地址
* 段信息
* 是否需要动态链接

---

# 三、创建新的进程地址空间

操作系统为程序创建一个新的虚拟地址空间。

典型布局：

```
High Address
+----------------------+
|        Stack         |
+----------------------+
|        Heap          |
+----------------------+
|   Shared Libraries   |
+----------------------+
|        Data          |
+----------------------+
|        Code          |
+----------------------+
Low Address
```

这个地址空间是 **虚拟内存**。

所以：

程序看到的是自己的独立世界。

---

# 四、加载程序段（Segments）

操作系统根据 ELF 的 **Program Header** 把文件中的段映射到内存。

例如：

```
file: hello

.text
.data
.bss
```

加载后：

```
memory:

0x400000  code (.text)
0x600000  data (.data)
0x601000  bss
```

注意：

这里不是简单复制，而是 **memory mapping**：

```
file → memory mapping
```

---

# 五、检查是否需要动态链接

如果程序依赖共享库：

例如：

```
libc.so
libm.so
```

ELF header 会包含：

```
INTERP
```

它指向 **动态链接器**。

Linux通常是：

```
/lib64/ld-linux-x86-64.so.2
```

这个程序就是 **Dynamic Linker**。

---

# 六、操作系统启动动态链接器

此时真正运行的第一个程序不是你的程序，而是：

```
ld-linux
```

它负责：

```
resolve symbols
load libraries
relocate addresses
```

流程：

```
hello executable
        ↓
dynamic linker
        ↓
load libc
        ↓
resolve printf
```

---

# 七、动态链接器加载共享库

动态链接器会读取：

```
DT_NEEDED
```

里面记录程序依赖：

例如：

```
libc.so
libm.so
libpthread.so
```

然后从系统库路径查找：

```
/lib
/usr/lib
```

加载这些库：

```
memory

hello
libc.so
libm.so
```

---

# 八、符号解析（Symbol Resolution）

例如你的程序写了：

```c
printf("hello");
```

编译后的代码其实只是：

```
call printf
```

但 `printf` 在：

```
libc.so
```

动态链接器会：

1️⃣ 找到 `printf` 地址

例如：

```
0x7f312ab420
```

2️⃣ 修改程序中的调用地址

```
CALL printf → CALL 0x7f312ab420
```

这一步叫：

**symbol binding**

---

# 九、重定位（Relocation）

如果程序或库被加载到不同地址：

需要修正所有引用。

例如：

```
printf offset = 0x120
library base = 0x7f312ab300
```

最终：

```
actual address = base + offset
```

---

# 十、初始化共享库

动态库可能包含初始化函数：

例如：

```
__libc_start_main
```

或者 C++：

```
global constructors
```

动态链接器会执行这些初始化代码。

---

# 十一、准备程序运行环境

动态链接器还会准备：

```
argc
argv
environment variables
```

例如：

```
main(int argc, char** argv)
```

这些参数是系统准备的。

---

# 十二、跳转到程序入口 `_start`

接下来：

```
dynamic linker → program entry
```

通常不是 `main`。

而是：

```
_start
```

这是编译器提供的启动代码。

---

# 十三、运行 C runtime

`_start` 会调用：

```
__libc_start_main
```

它会：

```
setup runtime
initialize stdlib
call main()
```

流程：

```
_start
   ↓
__libc_start_main
   ↓
main
```

---

# 十四、程序终于执行 `main`

现在才真正到你的代码：

```c
int main() {
    printf("hello");
}
```

程序开始执行。

---

# 十五、程序退出流程

当 `main` 返回：

```
main → exit → cleanup
```

操作系统：

```
destroy process
release memory
return status
```

---

# 十六、完整流程总结

从输入命令到程序运行：

```
./hello
   ↓
shell
   ↓
execve syscall
   ↓
kernel
   ↓
load ELF
   ↓
create virtual memory
   ↓
map program segments
   ↓
start dynamic linker
   ↓
load shared libraries
   ↓
resolve symbols
   ↓
run constructors
   ↓
jump to _start
   ↓
__libc_start_main
   ↓
main()
```

---

# 十七、为什么这和“组件架构”有关

动态链接其实就是：

**运行时加载组件。**

每个共享库就是组件：

```
libc.so
libssl.so
libpng.so
```

程序运行时：

```
load components
link components
run program
```

这就是软件架构里说的：

> **组件插件架构**

现代软件系统大量依赖这个机制。

例如：

* 浏览器插件
* IDE插件
* 游戏mod
* 数据库扩展

---

如果你愿意，我可以再给你讲一个 **很多高级工程师都没真正理解的东西**：

**为什么动态链接会导致 “DLL Hell / 依赖地狱” —— 以及现代系统是如何解决的。**

这个其实就是：

* npm
* Maven
* pip
* Docker

这些工具存在的根本原因。
```


####  Chap13. COMPONENT COHESION

- REP：复用/发布等同原则。软件复用的最小粒度应等同于其发布的最小粒度。
- CCP：共同闭包原则。总而言之，CCP 的主要作用就是提示我们要将所有可能会被一起修改的类集中在一处。
- CRP：共同复用原则。因此在 CRP 原则中，关于哪些类不应该被放在一起的建议是其更为重要的内容。简而言之，CRP 原则实际上是在指导我们：不是紧密相连的类不应该被放在同一个组件里。

CRP 原则实际上是 ISP 原则的一个普适版。ISP 原则是建议我们不要依赖带有不需要的函数的类，而 CRP 原则则是建议我们不要依赖带有不需要的类的组件。不要依赖不需要用到的东西。

Don’t depend on things you don’t need.

一般来说，一个软件项目的重心会从该三角区域的右侧开始，先期主要牺牲的是复用性。然后，随着项目逐渐成熟，其他项目会逐渐开始对其产生依赖，项目重心就会逐渐向该二角区域的左侧滑动。换句话说，一个项目在组件结构设计上的重心是根据该项目的开发时间和成熟度不断变动的，我们对组件结构的安排主要与项目开发的进度和它被使用的方式有关，与项目本身功能的关系其实很小。


#### Chap14. COMPONENT COUPLING


TOP-DOWN DESIGN 自上而下的设计

根据上述讨论，我们可以得出一个无法逃避的结论：组件结构图是不可能自上而下被设计出来的。它必须随着软件系统的变化而变化和扩张，而不可能在系统构建的最初就被完美设计出来。

### Part5. ARCHITECTURE

#### Chap15. WHAT IS ARCHITECTURE?

软件架构设计的主要目标是支撑软件系统的全生命周期，设计良好的架构可以让系统便于理解、易于修改、方便维护，并且能轻松部署。软件架构的终极目标就是最大化程序员的生产力，同时最小化系统的总运营成本。


- 在开发的早期阶段应该无须选择数据库系统，因为软件的高层策略不应该关心其底层到底使用哪一种数据库。事实上，如果软件架构师足够小心，软件的高层策略甚至可以不用关心该数据库是关系型数据库，还是分布式数据库，是多级数据库，还只是一些文本文件而已。
- 在开发的早期阶段也不应该选定使用的 Web 服务，因为高层策略并不应该知道自己未来要以网页形式发布。如果高层策略能够与 HTML、AJAX、JSP、JSF 或任何 Web 开发技术脱钩，那么我们就可以将对 Web 系统的选择推迟到项目的最后阶段。事实上，很有可能我们压根不需要考虑这个系统到底是不是以网页形式发布的。
- 在开发的早期阶段不应该过早地采用 REST 模式，因为软件的高层策略应该与外部接口无关。同样的，我们也不应该过早地考虑采用微服务框架、SOA 框架等。再说一遍，软件的高层策略压根不应该跟这些有关。
- 在开发的早期阶段不应过早地采用依赖注入框架（dependency injection framework），因为高层策略不应该操心如何解析系统的依赖关系。

说到这里，我想读者应该明白我的意思了。如果在开发高层策略时有意地摆脱具体细节的纠缠，我们就可以将与具体实现相关的细节决策推迟或延后，因为越到项目的后期，我们就拥有越多的信息来做出合理的决策。

一个优秀的软件架构师应该致力于最大化可选项数量。

A good architect maximizes the number of decisions not made.


#### Chap16. INDEPENDENCE


As we previously stated, a good architecture must support:

- The use cases and operation of the system.
- The maintenance of the system.
- The development of the system.
- The deployment of the system.


#### Chap17. BOUNDARIES: DRAWING LINES

正如我们之前所说，架构师们所追求的目标是最大限度地降低构建和维护一个系统所需的人力资源。那么我们就需要了解一个系统最消耗人力资源的是什么？答案是系统中存在的耦合尤其是那些过早做出的、不成熟的决策所导致的耦合。

那么，怎样的决策会被认为是过早且不成熟的呢？答案是那些决策与系统的业务需求（也就是用例）无关。这部分决策包括我们要采用的框架、数据库、Web 服务器、工具库、依赖注入等。在一个设计良好的系统架构中，这些细节性的决策都应该是辅助性的，可以被推迟的。一个设计良好的系统架构不应该依赖于这些细节?而应该尽可能地推迟这些细节性的决策，并致力于将这种推迟所产生的影响降到最低。

简单来说，通过划清边界，我们可以推迟和延后一些细节性的决策，这最终会为我们节省大量的时间、避免大量的问题。这就是一个设计良好的架构所应该带来的助益.


#### Chap29. CLEAN EMBEDDED ARCHITECTURE

1. “先让代码工作起来”——如果代码不能工作，就不能产生价值。
2. “然后再试图将它变好——通过对代码进行重构，让我们自己和其他人更好地理解代码，并能按照需求不断地修改代码。
3. “最后再试着让它运行得更快”——按照性能提升的“需求”来重构代码。



我们再来看另一个例子：有一个 LED 被连接到一个 GPIO 比特位上。固件可以直接操作 GPIO 比特位，而 HAL 则会提供一个 Led_TurnOn(5) 数。这种硬件抽象层的层次是相当低的。现在，假设我们想将抽象层次从硬件层次提升到软件/产品的层次。这时候就要弄清楚这个 LED 到底代表的是什么。假设它代表了电池电量不足，那么其固码（或该电路板的支持包）可能就会负责提供 Led_TurnOn(5) 函数，而 HAL 则负责提供 Indicate_LowBattery() 函数。由此可见，HAL 层是按照应用程序的需要来提供服务的。同时，我们也能看出来系统的每一个分层中都可以包含许多分层。相对于之前的固定分层法，这里更像是一种无限分层模式。总之，GPIO 位的对应关系应该是一个具体的实现细节，它应该与软件部分隔离。

目前的普适规则之一就是用头丈件来充当接口的定义。然而，如果真的要这样做的话，就需要小心控制头文件中的内容，尽量确保头文件中只包括函数声明，以及函数所需要的结构体名字和常量。


另外，不要在定义接口的头文件中包含只有具体实现代码才需要的数据结构、常量以及类型定义（typedef）。这不仅仅是架构是否整洁的问题，而是这样做可能会导致意外的依赖关系。总之，我们必须控制好实现细节的可见性，因为这些实现细节是肯定会变化的。关注实现细节的代码越少，它们所需的变更就越少

嵌入式编程人员应该多学习一些非嵌入式系统的编程经验。如果你从事的是嵌入式编程工作，相信你一定会从本章的建议中得到很多启发。
People who are developing embedded software have a lot to learn from experiences outside of embedded software. 
