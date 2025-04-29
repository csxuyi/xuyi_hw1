# 实现思路
### 先看algebra.h里关于结构体的定义和函数的声明，再在algebra.c里把函数的描述写完，写完后配置好cmake的环境，检查无误编译运行，输入样例数据，检查输出的结果是否正确
***
一下是函数功能实现的本地运行截图
# add_matrix
![enter image description here](https://pic1.imgdb.cn/item/68108d5b58cb8da5c8d42c4c.png)
# sub_matrix
![enter image description here](https://pic1.imgdb.cn/item/68108d6858cb8da5c8d42c51.png)
# mul_matrix
![enter image description here](https://pic1.imgdb.cn/item/68108d6858cb8da5c8d42c50.png)
# transpose_matrix
![enter image description here](https://pic1.imgdb.cn/item/68108d6858cb8da5c8d42c52.png)
# scale_matrix
![enter image description here](https://pic1.imgdb.cn/item/68108d6858cb8da5c8d42c53.png)
# det_matrix
![enter image description here](https://pic1.imgdb.cn/item/68108d6958cb8da5c8d42c54.png)
# inv_matrix`
![enter image description here](https://pic1.imgdb.cn/item/6810936a58cb8da5c8d44727.png)
# rank_matrix`
![enter image description here](https://pic1.imgdb.cn/item/6810936a58cb8da5c8d44726.png)
# trace_matrix
![enter image description here](https://pic1.imgdb.cn/item/6810936958cb8da5c8d44725.png)
> 前面忘记检验 row != col 时trace不存在的情况了