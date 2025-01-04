# [连接脚本](https://feng-qi.github.io/2016/09/07/linker-script/)

## 连接脚本样例

```c
/* link.ld */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K  /* Adjust based on your MCU */
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 128K  /* Adjust based on your MCU */
}

_estack = ORIGIN(RAM) + LENGTH(RAM);    /* Stack top */
_Min_Heap_Size = 0x8000;                /* 32KB heap */
_Min_Stack_Size = 0x2000;               /* 8KB stack */

SECTIONS
{
    /* Interrupt vectors first */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    /* Program code */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    /* Initialized data */
    .data :
    {
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    /* Uninitialized data */
    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    /* User heap */
    .heap :
    {
        . = ALIGN(8);
        _heap_start = .;
        . = . + _Min_Heap_Size;
        _heap_end = .;
        . = ALIGN(8);
    } >RAM
}
```



```c
/* memory map */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 3072K
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 192K
TCMRAM (rw)     : ORIGIN = 0x10000000, LENGTH = 64K
}

ENTRY(Reset_Handler)

SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 2K;
  __heap_size = DEFINED(__heap_size) ? __heap_size : 32K;

/* ISR vectors */
  .vectors :
  {
    . = ALIGN(4);
    KEEP(*(.vectors))
    . = ALIGN(4);
    __Vectors_End = .;
    __Vectors_Size = __Vectors_End - __gVectors;
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    /* the symbol ‘_etext’ will be defined at the end of code section */
    _etext = .;
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

   .ARM.extab :
  {
     *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

    .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    } >FLASH

  .ARM.attributes : { *(.ARM.attributes) } > FLASH

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array*))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* provide some necessary symbols for startup file to initialize data */
  _sidata = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
    /* the symbol ‘_sdata’ will be defined at the data section end start */
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    /* the symbol ‘_edata’ will be defined at the data section end */
    _edata = .;
  } >RAM AT> FLASH

  . = ALIGN(4);
  .bss :
  {
    /* the symbol ‘_sbss’ will be defined at the bss section start */
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    /* the symbol ‘_ebss’ will be defined at the bss section end */
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

 . = ALIGN(8);
  PROVIDE ( end = _ebss );
  PROVIDE ( _end = _ebss );

  _sitcmram = LOADADDR(.tcmram);

  .tcmram :
  {
    . = ALIGN(4);
    _stcmram = .;       /* create a global symbol at tcmram start */
    *(.tcmram)
    *(.tcmram*)

    . = ALIGN(4);
    _etcmram = .;       /* create a global symbol at tcmram end */
  } >TCMRAM AT> FLASH

  .stack ORIGIN(RAM) + LENGTH(RAM) - __stack_size :
  {
    PROVIDE( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
  } >RAM AT>RAM
}

 /* input sections */
GROUP(libgcc.a libc.a libm.a libnosys.a)
```





## 输出`section`语法

```c
SECTION [ADDRESS] [(TYPE)] : [AT(LMA)]
{
  OUTPUT-SECTION-COMMAND
  OUTPUT-SECTION-COMMAND
  /* ... */
} [>REGION] [AT>LMA_REGION] [:PHDR :PHDR ...] [=FILLEXP]
```

##### SECTION

SECTION 左右的空白、圆括号、冒号是必须的，换行符和其他空格是可选的。每个 OUTPUT-SECTION-COMMAND为以下四种之一，

1. 符号赋值语句
2. 一个输入section描述
3. 直接包含的数据值
4. 一个特殊的输出 section 关键字

##### ADDRESS

每个 loadable 或 allocatable 输出 section 通常包含两个地址：**VMA**(virtual memory address) 和 **LMA**(load memory address)。通常，VMA 和 LMA 是相同的。但在 嵌入式系统中，经常存在加载地址和执行地址不同的情况：比如将输出文件加载到开发 板的 flash 中(由 LMA)指定，而在运行时将位于 flash 中的输出文件复制到 SDRAM中 (由 VMA 指定)。

ADDRESS 是一个表达式，它的值用于设置 VMA。如果没有该选项且有 REGION 选项，那 么链接器将根据定位符号 `.` 的值设置该 section 的 VMA. 如果有该选项, 且该选项为`.`, 则将定位符号的值补齐到满足输出 section 对齐要求后的值，输出 section 的对齐要求为：该输出 section 描 述内用到的所有输入 section 的对齐要求中最严格的。

例子：

```
.text . : { *(.text)}
```

和

```
.text : { *(.text)}
```

这两个描述是截然不同的，第一个将 `.text` section 的 VMA 设置为定位符号的值， 而第二个则是设置成满足对齐要求后的定位符号的修调值。

ADDRESS 可以是一个任意表达式，比如 `ALIGN(0x10)` 将该 section 的 VMA 设置成 定位符号满足16 字节后的修调值。

>  注意：设置 ADDRESS 的值将会改变定位符号的值。

> More on ALIGN(exp)
>
> `ALIGN(exp)` 根据 exp 对齐后的位置返回当前 LC(定位符)。exp 必须是 2 的指数。 ALIGN 等价于：
>
> ```
> (. + exp - 1) & ~(exp - 1)
> ```
>
> ALIGN(exp) 本身并不改变 LC 的值，只是根据它的值进行算术运算。

有一个特殊的 output section 是 `DISCARD`, 用来丢弃 input sections，所有指定 到 `DISCARD` 的 input section 都不会被包含在输出文件里。

## 输入`section`语法

```c
FILENAME([EXCLUDE_FILE (FILENAME1 FILENAME2 ...)] SECTION1 SECTION2 ...)
```

FILENAME 文件名，可以是一个特定的文件的名字，也可以是一个字符串模式。
SECTION 名字，可以是一个特定的 section 名字，也可以是一个字符串模式。

例子：

`*(.text)`: 表示所有输入文件的 .text section

`(*(EXCLUDE_FILE (*crtend.o *otherfile.o) .ctors))`: 表示除 crtend.o、 otherfile.o 文件外的所有输入文件的 .ctors section。

`data.o(.data)`: 表示 data.o 文件的 .data section

`data.o`: 表示 data.o 文件的所有 section

`*(.text .data)`: 表示所有输入文件的 .text section 和 .data section，顺序是：
第一个文件的 .text section，第一个文件的 .data section；
第二个文件的 .text section，第二个文件的 .data section；



### INPUT命令

让我来解释一下 INPUT 命令和链接器的文件查找机制。

INPUT 命令是在链接器脚本中使用的一个命令，用来指定链接时需要包含的输入文件。它的基本语法是：

```
INPUT(file1 file2 ...)
```

举个具体例子：
```
/* 链接器脚本 */
INPUT(
  crt0.o      /* 启动文件 */
  main.o      /* 主程序目标文件 */
  libmath.a   /* 数学库 */
)
```

链接器查找文件的完整过程是这样的：

1. 首先检查链接命令行中直接指定的文件
```bash
ld -o program main.o lib.o -L/usr/lib
```

2. 然后检查链接器脚本中的 INPUT 命令指定的文件
```
INPUT(crt0.o main.o libmath.a)
```

3. 对于需要查找的文件，链接器会按以下顺序搜索：
   - 先在当前目录查找
   - 然后在 -L 选项指定的目录中查找
   - 最后在默认的系统库目录中查找

例如：
```bash
# 编译命令
ld -o program -L/usr/local/lib -L/opt/lib main.o

# 如果链接器脚本中有：
INPUT(libmath.a)

# 链接器会按这个顺序查找 libmath.a：
1. ./libmath.a             (当前目录)
2. /usr/local/lib/libmath.a  (-L 指定的第一个路径)
3. /opt/lib/libmath.a        (-L 指定的第二个路径)
4. /usr/lib/libmath.a        (默认系统库路径)
```

这种机制的优点是：
1. 可以在链接器脚本中集中管理所有需要的输入文件
2. 通过 -L 选项提供灵活的文件搜索路径配置
3. 可以方便地在不同环境下重用同一个链接器脚本，只需要调整 -L 指定的搜索路径

需要注意的是：如果某个文件在命令行和 INPUT 命令中都指定了，通常以命令行指定的为准。这给了用户在运行时覆盖链接器脚本默认设置的能力。

## 链接器是如何找到对应的文件的

当 FILENAME 是一个特定的文件名时，链接器会查看它是否在链接命令行内出现或在 INPUT 命令中出现。
当 FILENAME 是一个字符串模式时，链接器仅仅查看它是否在链接命令内出现。

注意：如果链接器发现某文件在 INPUT 命令内出现，那么它会在 -L 指定的路径内搜索该文件。

字符串模式内可以存在以下通配符[1](https://feng-qi.github.io/2016/09/07/linker-script/#fn.1)(4.6.4.2. Input Section Wildcard Patterns)：

- `*`: 表示任意多个字符
- `?`: 表示任意一个字符
- `[CHARS]`: 表示任意一个 CHARS 内的字符，可用 - 号表示范围，如 [a-z]
- `\`: 表示引用下一个紧跟的字符

在文件名内，通配符不匹配文件夹分隔符 `/` ，但当字符串模式仅包含 `*` 时除外。 任何一个文件的任意 section 只能在 SECTIONS 命令内出现一次。例如：

```
SECTIONS {
  .data : { *(.data) }
  .data1 : { data.o(.data) }
}
```

data.o 文件的 `.data` section 在第一个 `OUTPUT-SECTION-COMMAND` 命令内被使用了，那么在第二个 命令内将不会再被使用，也就是说即使链接器不报错，输出文件的 .data1 section 的内容也是空的。

注意：链接器依次扫描每个 `OUTPUT-SECTION-COMMAND` 命令内的文件名，任何一个文件的任何一个 section 都只能使用一次。

>  读者可以和 `-M` 连接命令选项来产生一个 map 文件，它包含了所有输入 section 到输出 section 的组合信息。

### 通用符号(COMMON)

通用符号(common symbol)的输入 section: 在许多目标文件格式中，通用符号并没有占用一个 section。链接器认为：输入文件的所有通用符号在名为 COMMON 的 section 内。

例子：

```
.bss { *(.bss) *(COMMON) }
```

这个例子中将所有输入文件的所有通用符号放入输出 `.bss` section 内。可以看到 COMMON section 的使用方法跟其他 section 的使用方法是一样的。有些目标文件格式把通用符号分成几类。

> 通用符号是C语言早期的一个特性，为了兼容性仍然存在
> `gcc -fno-common`  *# 禁用通用符号，遇到多重定义就报错*



### SORT命令

让我解释一下 `SORT()` 关键字的使用。

`SORT()` 可以对符合某个模式的所有名字进行字典序（按字母顺序）的递增排序。这在链接器脚本中特别有用。

例如：
```
SECTIONS
{
  .text : 
  {
    SORT(.text*)     /* 对所有 .text 开头的段进行排序 */
  }
}
```

具体示例：
假设你有以下目标文件中的段：

```
.text.init
.text.startup
.text.main
.text.helper
```

不使用 SORT：
- 段的顺序可能是随机的或按照目标文件在命令行中的顺序

使用 SORT：
```
SORT(.text*)  
```
将会按字典序排列：
```
.text.helper
.text.init
.text.main
.text.startup
```

SORT 也可以用在其他地方，比如文件名：
```
SORT(*)  /* 对所有输入文件名进行排序 */
```

这种排序机制的主要用途是：
1. 确保段的顺序是确定的，不依赖于目标文件在命令行中的顺序
2. 方便调试，因为段的布局是可预测的
3. 有助于保持构建的一致性和可重复性

SORT 用于文件名排序通常在以下场景中使用：

1. 在 INPUT 命令中确保文件加载顺序：
```
INPUT(SORT(*.o))   /* 按字母顺序加载所有 .o 文件 */
```

2. 在 SECTIONS 命令中指定文件的处理顺序：
```
SECTIONS
{
  .text : 
  {
    SORT(*.o)(.text)   /* 按文件名排序的顺序来处理每个.o文件中的.text段 */
  }
}
```

一个更完整的例子：
```
SECTIONS
{
  /* 初始化段 */
  .init : 
  {
    /* 按字母顺序处理所有init开头的目标文件中的.init段 */
    SORT(init*.o)(.init) 
    
    /* 然后按顺序处理其他目标文件中的.init段 */
    SORT(*.o)(.init)
  }

  /* 代码段 */
  .text :
  {
    /* 先处理main.o中的代码 */
    main.o(.text)
    
    /* 然后按顺序处理其他文件的代码 */
    SORT(*.o)(.text)
  }
}
```

使用 SORT 排序文件名的主要优点是：
1. 构建的确定性：每次构建产生的结果都是一样的
2. 便于调试：可以预知文件的处理顺序
3. 模块化管理：可以通过文件命名规则来控制模块的加载顺序