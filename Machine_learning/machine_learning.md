### 06 经典机器学习模型

#### 1. Decision Tree 决策树

Information Theory 信息论

Information function H(x) = -logP(x)

熵
Entropy(x) = Ex[H(x)] = -Ex p(x)logP(x)

信息熵
Information Entropy

信息增量
Information Gain (IG)

ID3 算法

将一个连续数据离散化
Discretization

将每一块数据的数量分成一样
在有多种数据时，使用数据的信息熵，将数据分类，是得总熵最小

##### Gini Split

Used in CART

GINI = kE(i=1)(ni/nGINI(I))