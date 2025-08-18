## [Matlab](https://www.bilibili.com/video/BV1ixgBzLEr2/?p=3&spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=0e4de0dd0c9aad54817599a7fef890c7)

### 基础操作

![image-20250727063907573](./assets/image-20250727063907573.png)

![image-20250727063924699](./assets/image-20250727063924699.png)

![image-20250727063942486](./assets/image-20250727063942486.png)

![image-20250727064047911](./assets/image-20250727064047911.png)

![image-20250727064333101](./assets/image-20250727064333101.png)

内积：行*列

外积：列*行

![image-20250727065857054](./assets/image-20250727065857054.png)

###### indexing

![image-20250727070247132](./assets/image-20250727070247132.png)

![image-20250727070716776](./assets/image-20250727070716776.png)

![image-20250727071020279](./assets/image-20250727071020279.png)

###### 增广矩阵

![image-20250727072327202](./assets/image-20250727072327202.png)

###### 矩阵操作

![image-20250727073043292](./assets/image-20250727073043292.png)

![image-20250728093847498](./assets/image-20250728093847498.png)

![image-20250728093913313](./assets/image-20250728093913313.png)

![image-20250728093938340](./assets/image-20250728093938340.png)

![image-20250728094026331](./assets/image-20250728094026331.png)

### 程式撰写

一种解释型脚本语言，不需要编译，一般存为.m文件

```matlab
for i=1:10
    x=linspace(1,10,101);
    plot(x, sin(x+1));
    print(gcf,'-deps', strcat('plot',num2str(i),'.ps'));
end
```

% 为注释符号

%% 为section分区模块，可以执行部分脚本。主要用于debug（二分查找）

![image-20250728100227565](./assets/image-20250728100227565.png)

![image-20250728100254374](./assets/image-20250728100254374.png)

![image-20250728100433552](./assets/image-20250728100433552.png)

![image-20250728100757259](./assets/image-20250728100757259.png)

![image-20250728101411956](./assets/image-20250728101411956.png)

![image-20250729075937213](./assets/image-20250729075937213.png)