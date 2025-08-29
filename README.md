# wwt的自学指南

Somebody has to win, so why not be me?

首先借用`Whynot`大佬高中时的励志名言开场。`Whynot`不仅优秀，努力，还满怀赤诚之心，值得你我作为榜样。

想了许久，也不知道该如何为我这杂乱无章的笔记写简介。或许留下我的来时路，对大家有些帮助。

## 首先是入门语言`C`

课程: [王道训练营-C语言教程](https://www.bilibili.com/video/BV1bQ4y1A7kB?spm_id_from=333.337.search-card.all.click&vd_source=0be7e6585a5e2d139cd3524579615507)

书籍: "The C Programming Language" "C程序设计语言（第2版）" 英文一般的可以中英文对照，这本书的英文难度不大，可以作为英文起步，强迫自己适应。

课程相关：该课程由华为前操作系统员工讲授，讲课水平可以，值得一看。需要一定的数据结构基础，如果基础比较薄弱，也推荐王道考研408的四大课。

题外话：首先学会使用google和英文是成为一名"优秀"程序员的必经之路。这两项主要是增强你信息获取的能力，花更短的时间获取到想要的资源，无论是在学习还是工作上。其次，阅读书籍虽然效率上比向AI或前辈请教慢，但是理解更为深刻。好的书籍能带你走进一个世界。**持续阅读**是质变的必要条件。


## 计算机基础:

推荐课程: [15-213: Introduction to Computer Systems, Sep. 1, 2015](https://scs.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=03308c94-fc20-40d8-8978-1a9b81c344ed)

推荐书籍: "Computer Systems A Programmer’s Perspective-Pearson (2015) - Randal E. Bryant_ David R"
        中文对照：“深入理解计算机系统

课程相关：卡内基梅隆大学的经典课程，由 Randal E. Bryant 和 David R. O’Hallaron 两位大师主讲。它不仅教你写代码，还让你理解编译、内存、汇编、网络、并发这些核心概念。学过之后，你会发现写程序和调 bug 的思路完全不一样了。
这门课有配套的作业和实验，几个实验都很经典，设计的也很好，必做。比如 bomb lab (调试汇编找炸弹密码)、malloc lab (自己实现内存分配器)、proxy lab (写一个并发网络代理)。这些实验超级经典，挑战性大，但学到的东西很有成就感。光看课，不动手效果会大打折扣。


## 操作系统:

推荐课程: [6.S081: Operating System Engineering, Fall 2021](https://pdos.csail.mit.edu/6.828/2021/index.html)

推荐书籍: "xv6: a simple, Unix-like teaching operating system"

课程相关：麻省理工学院的操作系统核心课程，由 Robert Morris 教授主讲，被很多计算机专业学生认为是操作系统学习的黄金标准。如果你想真正搞懂操作系统，极其推荐。它不像一般课只讲原理，而是带你亲手改一个小型 Unix 系统（xv6）。你能一步步学会进程、内存、文件系统、并发这些核心机制。适合想在想在系统编程、嵌入式、内核开发方向深耕的人。也是我最喜欢的一门课程。

推荐课程： [南京大学 蒋炎岩 操作系统：设计与实现](https://jyywiki.cn/OS/2024/)

推荐书籍："Operating Systems: Three Easy Pieces Arpaci-Dusseau Books, 2018."

课程相关：蒋炎岩教授是个纯粹的人，这个课程是为数不多的优秀中文课程。jyy yyds! 这门课不光讲原理，还会手把手带你从零写一个操作系统，亲手实现 进程调度、内存管理、文件系统。


## 计算机网络:

推荐课程: [CS-340 Intro to Computer Networking](https://www.youtube.com/playlist?list=PLWl7jvxH18r3nnotitKkyAjq268PQGc0-)

推荐书籍: "Computer Networking: A Top-Down Approach"

课程相关: 计算机网络相关的好课不好找，这是我能够找到的最好课程。即使你不从事网络相关的工作，网络的学习还是很有必要的，TCP/IP 协议是一个十分经典的协议。学好网络，是你构建一个好的通讯协议的基础。同时他会让你对分层思想有更深刻的理解，为你的程序架构设计添加灵感。同时也推荐一本程序架构设计的书籍， "Software Architecture in Practice(4th)"。


## 数据库(TODO)：

推荐课程：[CMU 15-445/645 :: Intro to Database Systems (Fall 2022)](https://15445.courses.cs.cmu.edu/fall2022/)

推荐书籍："Database System Concepts Seventh Edition Avi Silberschatz Henry F. Korth S. Sudarshan"

课程相关：卡内基梅隆大学的数据库系统入门课。它不仅教怎么用 SQL，而是带你从零实现一个数据库的核心功能。讲课很生动，而且编程作业能真正提升系统编程能力。如果你对后端、系统或者数据库感兴趣，这门课是世界一流的起点。


## 分布式系统(TODO):

推荐课程：[MIT 6.824: Distributed Systems (Spring 2020)](http://nil.lcs.mit.edu/6.824/2020/)

推荐书籍："Distributed Systems: Principles and Paradigms" "Distributed Systems, 3rd Edition"

课程相关：这是 MIT 的研究生课程，专注于 分布式系统的核心原理和实践，比如一致性、容错、复制、MapReduce、Raft 等，是计算机系统方向里非常经典的课程。6.824 是分布式系统入门和进阶的“金字招牌”，很多大厂工程师和研究人员都学过。
