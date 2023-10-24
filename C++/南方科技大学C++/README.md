# Programming in C/C++ Efficiently

课程视频:https://www.bilibili.com/video/BV1Vf4y1P7pq

资料仓库:https://github.com/ShiqiYu/CPP/blob/main/README.md

## Chapter 2

https://en.cppreference.com/w/cpp/language/implicit_conversion

| 类型     | 转换目标类型 | 转换方法                    |
| -------- | ------------ | --------------------------- |
| 浮点数   | 整数         | 舍弃小数位，2.8->2          |
| 低位整数 | 高位整数     | 符号位扩展                  |
| 高位整数 | 低位整数     | 直接截断，舍弃高位          |
| 有符号数 | 无符号数     | 转为无符号数，但底层bit不变 |

short范围大约为正负3万多，char范围大约为正负128

只有int,long,float,double四种运算类型，如果所需有需要计算的数都能用int表达，则内部转换为int进行计算，如果位数不够则转为long。如两个字符char类型相加，底层是将它们都转换为int再进行运算。

运算式中含有unsigned int则都转为unsigned,如果含有float,则都转为float

转换方向：int->unsigned int->float