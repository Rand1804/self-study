## [以ffmpeg为例说说C代码的设计理念](https://www.bilibili.com/video/BV1M9XeYJE7V/?spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=0e4de0dd0c9aad54817599a7fef890c7)

1. 容器

   1. 数组

   2. 双链表： 在任意位置插入或删除（查找效率低O(n))

   3. 哈希表：仅高效查找

      ```c
      struct list* hash[97];(元素个数为质数效率更高)
      i = value % 97;
      
      有时在非常大的哈希表时，也会使用2的指数（32，64...)
      优势在于可以使用`value & (size-1)`代替`value % size`
      ```

   4. 单链表：仅在头部删除和增加，类似于stack，push，pop，永远从栈顶增加和删除元素

   5. 二叉树：红黑树（保证平衡性，不会退化为双链表），B+树（在磁盘上更注重局部性，方便一次读取一个扇区，一般用于数据库）， 增删查改都有不错的性能

   6. 图：一般用于寻路

2. 数据

3. 分步

4. 分层

5. 模块

6. 接口
