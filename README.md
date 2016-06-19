# datastruct

标签： 数据结构 算法
本项目包括的是一些数据结构和算法分析的代码。

----------


## 1. 邻接表表示的图
### 1.概述
用模板形式重新定义图的类，模板类型主要用于邻接表的定义中。
### 2.使用环境
VS2013
### 3.使用说明

```C
    //①创建graph对象
    int data[7] = { 1, 1, 1, 1, 1, 1 ,1};
	Graph <int, int> graph(7, data, false);
	//②插入边，和对应权重
    graph.insertEdge(0, 1, 2);
	graph.insertEdge(1, 4, 10);
	graph.insertEdge(4, 6, 6);
	graph.insertEdge(6, 5, 1);
	graph.insertEdge(2, 5, 5);
	graph.insertEdge(2, 0, 4);
	graph.insertEdge(0, 3, 1);
	graph.insertEdge(3, 2, 2);
	graph.insertEdge(3, 5, 8);
	graph.insertEdge(1, 3, 3);
	graph.insertEdge(3, 4, 2);
	graph.insertEdge(3, 6, 4);
	//③输出图
    graph.printGraph();
	//④输出最短路径
    graph.shortestPath(2, 6);
	printf("\n");
	//⑤输出最小生成树
	graph.minimalTree();
```
### 4.算法分析
参照数据结构与算法分析---C语言描述，图的章节。


----------
## 2. 邻接表表示的图
### 1.概述
建立堆的模板建立，通过使用一维数组存储堆。同时理解如何将二叉树表示为堆。建立一个堆结构，将其调整为最小堆。
### 2.使用环境
VS2013
### 3.使用说明
```C
        //①创建minheap对象 ，插入数据
    int data[10] = { 93,53,72,48,30,45,36,18,35,15 };
	MinHeap <int> minheap(10,data)
        //②删除最小结点并输出堆
	minheap.removeMin();
	minheap.printHeap();
```
### 4.算法分析
参照数据结构与算法分析---C语言描述，堆的章节。


----------
## 3. 邻接表表示的图
### 1.概述
建立Huffman树数据结构，应用该结构生成Huffman编码。
### 2.使用环境
VS2013
### 3.使用说明
```C
       // ①创建链散列表对象：
    Chaining <int> *chain= new Chaining<int>();
	int i = chain->hashFunction("ss");
	int j = chain->hashFunction("s");
       // ②散列键值对	
    chain->hash("s", 1);
	chain->hash("s", 2);
	chain->hash("ss", 2);
       // ③获取给定key值的value
	int k = chain->getValue("ss");
        //④打印散列表	
    chain->printTable();

```
### 4.算法分析
参照数据结构与算法分析---C语言描述，散列的章节。


----------
## 4. 邻接表表示的图
### 1.概述
建立一个基于开散列方法（链地址法）的散列表数据结构。散列到同一个值的所有元素都保留到一个链表中。
### 2.使用环境
VS2013
### 3.使用说明
```C
        //①创建编码数据和编码权重数据，创建霍夫曼树对象
    int dataa[7] = { 1,2,3,4,5,6,7};
	int datab[7] = {10,15,12,3,4,13,1};
	HuffTree <int,int> huffman(7,dataa,datab);
        //②创建霍夫曼树	
    huffman.createHuffTree();
        //③中序遍历输出霍夫曼树
	huffman.printHuffTree(huffman.getRoot());
	printf("\n");
        //④输出霍夫曼编码
	huffman.printHuffCode(huffman.getRoot());


```
### 4.算法分析
参照数据结构与算法分析---C语言描述，贪婪算法的章节。







