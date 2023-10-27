# Programming in C/C++ Efficiently

课程视频:[https://www.bilibili.com/video/BV1Vf4y1P7pq]

资料仓库:[https://github.com/ShiqiYu/CPP/blob/main/README.md]

## Chapter 2

[https://en.cppreference.com/w/cpp/language/implicit_conversion]

| 类型     | 转换目标类型 | 转换方法                    |
| -------- | ------------ | --------------------------- |
| 浮点数   | 整数         | 舍弃小数位，2.8->2          |
| 低位整数 | 高位整数     | 符号位扩展                  |
| 高位整数 | 低位整数     | 直接截断，舍弃高位          |
| 有符号数 | 无符号数     | 转为无符号数，但底层bit不变 |

short范围大约为正负3万多，char范围大约为正负128

只有**int,long,float,double**四种运算类型，如果所需有需要计算的数都能用int表达，则内部转换为int进行计算，如果位数不够则转为long。如两个字符char类型相加，底层是将它们都转换为int再进行运算。

运算式中含有unsigned int则都转为unsigned,如果含有float,则都转为float

转换方向：int->unsigned int->float

## Chapter 3

int m = (b = 8);
m的值为8，赋值表达式的值为他的右值

二维数据在传递时必须带有一列的元素个数，编译器需要这个值来确定第二行从哪里开始
如：`a[][3]`

```c++
enum datatype {TYPE_INT8=1, TYPE_INT16=2, TYPE_INT32=4, TYPE_INT64=8};
struct Point {
    enum datatype type;
    union {
        std::int8_t data8[3];
        std::int16_t data16[3];
        std::int32_t data32[3];
        std::int64_t data64[3];
    };
};

size_t datawidth(struct Point pt) {
    return size_t(pt.type) * 3;
}
int64_t l1norm(struct Point pt) {
    int64_t result = 0;
    switch(pt.type) {
        case (TYPE_INT8):
            result = abs(pt.data8[0]) +
                    abs(pt.data8[1]) +
                    abs(pt.data8[2]);
            break;
        //...
    }
}
```

> The int is boring, so I've left it out. But look at the difference between the int* and the vector<int>: the int* is the same in f1 and f2; it's what you would call a "shallow copy". The vector<int> however is different between f1 and f2; it's what you would call a "deep copy".
> What's actually happened here is that the default operator = in C++ behaves as if the operator = for all of its members were called in order. The operator = for ints, int*s, and other primitive types is just a byte-wise shallow copy. The operator = for vector<T> performs a deep copy.
> So I would say the answer to the question is, No, the default assignment operator in C++ does not perform a shallow copy. But it also doesn't perform a deep copy. The default assignment operator in C++ recursively applies the assignment operators of the class's members.