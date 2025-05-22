## Introduction
数据压缩的字段经常被成为`source coding`。压缩后的数据与他的前文甚至后文相关，压缩前的数据也叫无记忆源数据，独立分布。`A memoryless source is also termed “independent and identically distributed” or IIID.`
所有压缩算法都基于相同的原理，即从源文件的原始数据中删除冗余来压缩数据。
- 字母冗余(alphabetic redundancy): 字母e出现的最频繁，z出现的最少
- 上下文冗余(contextual redundancy): 字母Q后面总是跟着字母U
压缩的原理：去除重复，也解释了为什么已经压缩的文件不能被更进一步压缩。
大多数随机或接近随机的文件是无法压缩的。
许多现代压缩方法通常是非对称的，及解压和压缩并不耦合，只需要能正确运行即合规。导致解压和压缩速度并不相同。
大多数压缩算法是**流处理模式**，即输入一个或多个字节都进行处理，直到收到文件结束符。另一些方法如`Burrows-Wheeler`是块处理的，输入流一块一块的压缩，块的大小由用户定义，且极大的影响压缩效率。
大多数压缩是**物理压缩**，他们只关注输入流中的比特，而忽略具体的含义。与之相对的是**逻辑压缩**，他们会查看源流中的单个数据项。
- 衡量压缩的指标
	- 压缩率 `Compression ratio =  size of the output stream / size of the input stream`
	- 压缩因子`Compression factor = size of the input stream / size of the output stream`
	- 压缩速度 `cycles per byte (CPB)` 平均压缩一个字节需要几个机器周期

## 1. Basic Techniques
### 1.1 Intuitive Compression
1. 盲文(Braille)
![[Pasted image 20250520172715.png]]
2. 不可逆压缩(Irreversible Text Compression)
		例如代码文件中多个连续的空格可以替换为一个。书籍可以都转换为大写或者小写字母，然后从8位字符减少到使用5位。
3. 一些简单的压缩技巧(Ad Hoc Text Compression)
	1. 如果一个文本里有很多空格，可以用一个位串来表示哪一位是空格，从而删除文本中的所有空格
	2. ASCII实际上只使用了7个bits，所以可以使用7个bits代替8个bits
	3. 如果一个文本中只有40个不同的字符，可以将3个字符组合成一个三元组，所以一个三元组就有40^3 的可能性，因为2^16 大于40^3 , 所以用16位即可表示。假如原本每个字符需要一个字节，则三个字符需要24位。
	4. 如果一个文本中仅包含大写字母，数字和一些常用符合，可以使用旧的6位`CDC display code`,在二代和少量三代计算机上使用过。他们没有显示器，仅将输出输入打印机。![[Pasted image 20250521105159.png]]
	5. `Baudot code`波特码，在一代和二代计算机时广泛用于电报上，用一个5bits代表两种字符，字母或数字，在使用移位码来区分数字还是字母。最终达到使用5bits可以最多表达32 × 2 − 2 = 62个字符![[Pasted image 20250521110013.png]]
	6. 字典数据通常可以使用**前端压缩**，因为此类列表中相邻的单次往往前n个字符是相同的，就可以使用m个字符来替换他们![[Pasted image 20250521133341.png]]
	7. 使用4个bits表示常用的15个字符和一个转义字符，其他字符则用转义字符加上8bits的ASCII。最后再用一bit表示是否使用压缩如果压缩过后反而比之前大了
### 1.2 Run-Length Encoding
The n consecutive occurrences of a data item are called a run length of n, and this approach to data compression is called run-length encoding or RLE.
一个游程编码的变体是二元字符编码(**digram encoding**),原理是替换文本中经常出现的字符对替换为一个ASCII中不会出现的编码。
另一个相似的变体叫做**模式匹配(pattern substitution)**，适用于代码文件，将for，print等经常出现的短语替换为特殊编码
### 1.3 相对编码(Relative Encoding)
使用在数据变化较小或者字符串和彼此比较相似的情况。前者的例子是遥测，在遥测中，温度变化的数值不会太大，可以发送第一个温度，然后后续的温度会相对值来表示
### 1.4 The BinHex 4.0 Format
因为ASCII格式仅使用了7bits，所以网络传输时许多设备默认忽视了首字节，会导致传输bin文件时不安全。所以BinHex就是将任何文件转换为文本文件

## 2. Statistical Methods

## 3. Dictionary Methods
字典方法不依赖于数据的统计模型，他们选择符合的字符串，使用字典将他们编码为一个token。字典包含字符串，可以是静态的或者是动态(自适应)。前者是永久性的，有时允许添加字符串但不允许删除；而后者保存先前在输入流中找到的字符串，允许在读取新输入时添加和删除字符串。
**静态字典**：适用于特定场景，所有需要解压和压缩的pc都具备一个相同的字典
**自适应字典**：更为通用和合理。这种方法可以从一个空字典或一个较小的默认字典开始，在输入流中找到单词时将其添加到字典中，并删除旧单词，因为较大的字典会减慢搜索速度。这种方法包含一个循环，每次迭代都从读取输入流并将其分解（解析）为单词或短语开始。然后，它应该在字典中搜索每个单词，如果找到匹配项，则在输出流中写入一个标记。否则，应写入未压缩的单词并将其添加到字典中。每次迭代的最后一步检查是否应该从字典中删除旧单词。

### 3.1 String Compression
一般来说，基于字符串的压缩方法比基于字符的方法更为高效。因为相同字符串的出现概率方差更大。![[Pasted image 20250522151839.png]]

### 3.2 Simple Dictionary Compression
一个简单的两遍法：第一遍先读取整个文件，然后准备一个所有找到的不同字节的列表。第二遍使用这个列表去实际压缩数据。
1. 列表包含所有字节的出现次数，然后从高到低排列，因为只有一个字节，所以列表最多有256个元素。
2. 这个排序的列表作为字典，被写入压缩文件中，最开头的一个字节代表长度
3. 然后将每个字节替换为3bits表示在字典中的索引长度+索引(即4-11bytes)，因为越高频的字节索引越小，即所需的长度越短。从而实现压缩。但当256种可能的字节都均匀出现时，会出现扩张(expansion)!
### 3.3 LZ77 (Sliding Window)
token (16, 3, e)
- 16(offset)：代表当前位置向前移动多少位
- 3(length)：代表复制几个字节
- e(character)：代表后一个字符
![[Pasted image 20250522164405.png]]
假设当前已经解析到的内容为`... sir␣sid␣eastman␣easily␣t`，然后读到token(16, 3, e),即向前移动16位，指向'e'在单词"eastman"，然后复制3位，即复制’eas‘，最后添加字符e，最终解析出来为`sir␣sid␣eastman␣easily␣tease`。该方法使用前面解析出来的内容作为后面的字典。当向前搜索时一个都没匹配上，那么位移长度和复制长度都为0，最后一个为没匹配上的字节，这也是为什么一个token需要第三个成员。
- offset位的大小为log_2S, S是搜索缓冲(search buffer)的长度(一般为10-12bits)
- length位的大小为log_2(L-1),L的长度为look-ahead buffer的长度。长度通常比较短
- character位的大小通常为8bits，但是更通用的来说为log_2A,A是alphabet size
1-symbol token (0, 0, . . .) 通常为11+5+8= 24bits
初次看LZ77方法似乎不对文本进行假设，也不关心任何符合的出现频率。但由于搜索缓冲的长度限制，实际上LZ77假设相近的数据是相似的。
### 3.4 LZSS