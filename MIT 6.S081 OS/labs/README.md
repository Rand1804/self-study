Certainly! Here's a list of frequently used GDB commands that are essential for effective debugging. These commands can help you control the execution flow, inspect the state of a program, set breakpoints, and more.

### Basic Navigation
- **`run` (or `r`):** Starts the execution of your program in GDB. You can also pass arguments to your program using this command.
- **`continue` (or `c`):** Resumes the execution of your program after it has been stopped (e.g., at a breakpoint).
- **`next` (or `n`):** Executes the next line of your program, stepping over function calls.
- **`step` (or `s`):** Executes the next line of your program, stepping into function calls.
- **`finish`:** Runs until the current function is finished and returns to the caller.

### Breakpoints and Watchpoints
- **`break` [location] (or `b` [location]):** Sets a breakpoint at the specified location. The location can be a function name, line number, or address.
- **`watch` [expression]:** Sets a watchpoint for the given expression (e.g., a variable). The program will stop whenever the expression's value changes.
- **`info breakpoints`:** Lists all breakpoints and watchpoints.
- **`delete` [breakpoint number]:** Deletes the specified breakpoint or watchpoint.
- **`disable` [breakpoint number]:** Disables the specified breakpoint or watchpoint without deleting it.
- **`enable` [breakpoint number]:** Re-enables a previously disabled breakpoint or watchpoint.

### Inspecting the Program State
- **`print` [expression] (or `p` [expression]):** Evaluates and prints the value of the expression.
- **`info locals`:** Displays local variables of the current function.
- **`info args`:** Shows the arguments of the current function.
- **`backtrace` (or `bt`):** Displays the call stack (or backtrace) showing function calls that led to the current point in the program.
- **`list` (or `l`):** Shows the source code around the current line or specified location.

### Controlling Execution
- **`set variable` [variable]=[value]:** Changes the value of a variable.
- **`signal` [signal]:** Sends a specified signal to the program.
- **`kill`:** Terminates the execution of the program being debugged.

### Miscellaneous
- **`info registers`:** Displays the contents of CPU registers.
- **`disassemble` [function]:** Disassembles the machine code of a specified function.
- **`layout src`:** Switches to the Source layout, showing the source code, assembly, and registers.
- **`help`:** Provides information about GDB commands.

### Exiting GDB
- **`quit` (or `q`):** Exits GDB.

These commands form the foundation of navigating and utilizing GDB for debugging. As you become more experienced, you may find additional, more advanced commands useful for specific scenarios. Remember that GDB is a powerful tool, and mastering its commands can significantly enhance your debugging efficiency.

有关RISC-V的一件有意思的事情是，虚拟内存地址都是64bit，这也说的通，因为RISC-V的寄存器是64bit的。但是实际上，在我们使用的RSIC-V处理器上，并不是所有的64bit都被使用了，也就是说高25bit并没有被使用。这样的结果是限制了虚拟内存地址的数量，虚拟内存地址的数量现在只有2^39个，大概是512GB。当然，如果必要的话，最新的处理器或许可以支持更大的地址空间，只需要将未使用的25bit拿出来做为虚拟内存地址的一部分即可。

在剩下的39bit中，有27bit被用来当做index，**12bit被用来当做offset。offset必须是12bit**，因为对应了一个page的4096个字节。

物理内存地址是56bit，其中44bit是物理page号（PPN，Physical Page Number），剩下12bit是offset完全继承自虚拟内存地址（也就是地址转换时，只需要将虚拟内存中的27bit翻译成物理内存中的44bit的page号，剩下的12bitoffset直接拷贝过来即可）。

选择56bit而不是64bit是因为在主板上只需要56根线。

这个page table最多会有2^27个条目（虚拟内存地址中的index长度为27），这是个非常大的数字。如果每个进程都使用这么大的page table，进程需要为page table消耗大量的内存，并且很快物理内存就会耗尽。

所以实际上，硬件并不是按照这里的方式来存储page table。从概念上来说，你可以认为page table是从0到2^27，但是实际上并不是这样。实际中，page table是一个多级的结构。下图是一个真正的RISC-V page table结构和硬件实现。

![img](https://906337931-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-MHZoT2b_bcLghjAOPsJ%2F-MKKjB2an4WcuUmOlE__%2F-MKPwJezGQDkWaLDRuDs%2Fimage.png?alt=media&token=654cbddc-fab3-4180-8bd7-d275c63ae67f)

我们之前提到的虚拟内存地址中的27bit的index，实际上是由3个9bit的数字组成（L2，L1，L0）。

一个directory是4096Bytes，就跟page的大小是一样的。Directory中的一个条目被称为PTE（Page Table Entry）是64bits，就像寄存器的大小一样，也就是8Bytes。所以一个Directory page有512个条目。

所以实际上，SATP寄存器会指向最高一级的page directory的物理内存地址，之后我们用虚拟内存中index的高9bit用来索引最高一级的page directory，这样我们就能得到一个PPN，也就是物理page号。这个PPN指向了中间级的page directory。

当我们在使用中间级的page directory时，我们通过虚拟内存地址中的L1部分完成索引。接下来会走到最低级的page directory，我们通过虚拟内存地址中的L0部分完成索引。在最低级的page directory中，我们可以得到对应于虚拟内存地址的物理内存地址。

从某种程度上来说，与之前一种方案还是很相似的，除了实际的索引是由3步，而不是1步完成。这种方式的主要优点是，如果地址空间中大部分地址都没有使用，你不必为每一个index准备一个条目。举个例子，如果你的地址空间只使用了一个page，4096Bytes。

> 学生提问：既然每个物理page的PPN是44bit，而物理地址是56bit，我们从哪得到缺失的12bit？（这个学生嘟囔了半天，我猜他是要问这个。其实12bit直接从虚拟地址的12bit offset继承就可以了，但是可能这个问题太简单了，Frans教授似乎理解错了问题。）
>
> Frans教授：所有的page directory传递的都是PPN，对应的物理地址是44bit的PPN加上12bit的0（注，也就是page的起始地址，因为每个page directory都使用一个完整的page，所以直接从page起始地址开始使用就行）。如果我们查看这里的PTE条目，它们都有相同的格式，其中44bit是PPN，但是寄存器是64bit的，所有有一些bit是留空的。实际上，支持page的硬件在低10bit存了一些标志位用来控制地址权限。

![image(17)](/home/wuwt/note/self-study/MIT 6.S081 OS/labs/assets/image(17).png)

## Kernel Page Table

![img](https://906337931-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-MHZoT2b_bcLghjAOPsJ%2F-MK_UbCc81Y4Idzn55t8%2F-MKaY9xY8MaH5XTiwuBm%2Fimage.png?alt=media&token=3adbe628-da78-472f-8e7b-3d0b1d3177b5)