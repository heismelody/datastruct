#include <limits>
#define MAXSIZE 15;
#define NOTAVERTEX (-1);
template<class ValueType,class WeightType> class Graph{
private:
	struct Edge
	{
		int index;
		ValueType value;
		WeightType weight;
		Edge *next;
	};
	struct Vert
	{
		int index;
		ValueType value;
		Edge *edge;
	};

	//Dijkstra算法所使用的辅助表，参照
	//《数据结构与算法分析--C语言描述》
	struct TableEntry          
	{
		Edge * adjacency;
		bool known;
		WeightType dist;
		int pathIndex;
	};
	TableEntry * table;

	Vert * vert;					//点结构体数组
	int numEdge;					//边数
	int numEdgeOfEachVert;          //每个顶点的边数
	int numVert;					//顶点数
	int maxsize;
	bool is_dir;                    //是否为有向图,true为有向图

public:
	Graph(int size,ValueType * vertdata,bool isdir)
	{
		this->maxsize = MAXSIZE;
		if(size > 0 && size <= maxsize)
		{
			this->maxsize = MAXSIZE;
			this->numVert = size;
			vert = new Vert[maxsize];
			for (int i = 0; i < numVert; i++)
			{
				vert[i].index = i;
				vert[i].value = vertdata[i];
				vert[i].edge = NULL;
			}
		}
		this->is_dir = isdir;
	}							

	/* 
	* 获取图的顶点个数
	* @param 无
	* @return int 顶点个数
	*/
	int getVert(){ return this->numVert; }					
	
	/* 
	* 获取图的边数
	* @param 无
	* @return int 边数
	*/
	int getEdge(){ return numEdge; }							
	
	/* 
	* 返回顶点的数据值
	* @param int index(顶点数组中的序号)
	* @return ValueType value
	*/
	ValueType getValue(int index)
	{
		if (index < getVert() && this->vert[index].value){ return this->vert[index].value; }
		else { return NULL; }
	};

	/* 
	* 返回边上的权值
	* @param int vert1 顶点1，int vert2 顶点2
	* @return Weight v1->v2边的权重
	*/
	WeightType getWeight(int vert1, int vert2)
	{
		if (vert1 < numVert && vert2 < numVert)
		{
			Edge * curEdge = vert[vert1].edge;
			while (curEdge->next)
			{
				curEdge = curEdge->next;
				if (curEdge->index == vert2){ return curEdge->weight; }
			}
		}
		else { return NULL; }
	};

	/* 
	*  查找index顶点的邻接顶点
	* @param int index(顶点数组中的序号)
	* @return 边结构体链表的头指针
	*/
	Edge * getAdjacency(int index)
	{
		return vert[index].edge;
	};

	/* 
	* 查找顶点是否存在
	* @param int vert(顶点数组中的序号)
	* @return true存在
	*/
	bool isVertExist(int vert){ return vert < numVert ? true : false; };

	/* 
	* 插入一个顶点
	* @param int insertindex 插入顶点的序号 
	*        ValueType insertval 插入顶点的值
	*/
	bool insertVer(int insertindex, ValueType insertval)
	{
		if (insertindex == numVert)
		{
			numVert++;
			vert[insertindex].index = insertindex;
			vert[insertindex].value = insertval;
			vert[insertindex].edge = NULL;
			return true;
		}
		else { return false; }
	};

	/* 
	* 插入一条包含权重的边
	* @param int vert1 如果为有向图为起始点, 
	*        int vert2 如果为有向图为终止点, 
	*        WeightType weight 表示权重
	* @return true 插入成功
	*/
	bool insertEdge(int vert1, int vert2, WeightType weight)
	{
		if (isVertExist(vert1) && isVertExist(vert2))
		{
			if (is_dir)
			{
				Edge * firstEdge = vert[vert1].edge;
				if (!firstEdge)
				{
					Edge * insertEdge = new Edge();
					insertEdge->index = vert2;
					insertEdge->value = vert[vert2].value;
					insertEdge->weight = weight;
					
					vert[vert1].edge = insertEdge;
					return true;
				}
				else
				{
					Edge * insertEdge = new Edge();
					insertEdge->index = vert2;
					insertEdge->value = vert[vert2].value;
					insertEdge->weight = weight;
					insertEdge->next = vert[vert1].edge;

					vert[vert1].edge = insertEdge;
					return true;
				}	
			}
			else
			{
				this->is_dir = true;
				this->insertEdge(vert1, vert2, weight);
				this->insertEdge(vert2, vert1, weight);
				this->is_dir = false;
				return true;
			}
		}
		else{ return false; }	
	};

	/* 
	* 删除一个顶点
	* @param int index(顶点数组中的序号)
	*/
	bool removeVer(int index)
	{
		if (index < numVert)
		{
			vert[index].value = NULL;
			vert[index].edge = NULL;
			for (int i = 0; i < numVert; i++)
			{
				Edge * curEdge = vert[i].edge;
				if (curEdge)
				{
					if (curEdge->index == index)
					{
						vert[i].edge = curEdge->next;
						continue;
					}
					else
					{
						while (curEdge->next)
						{
							Edge * lastOfcurEdge = curEdge;
							curEdge = curEdge->next;
							if (curEdge->index == index)
							{
								lastOfcurEdge->next = curEdge->next;
								continue;
							}
						}
					}		
				}
			}
			return true;
		}
		else { return false; }
	};

	/* 
	* 删除一条边
	* @param int vert1(有向图中起始顶点数组中的序号)
	*        int vert2（有向图中终止顶点数组中的序号） 
	* @return 边数
	*/
	bool removeEdge(int vert1, int vert2)
	{
		Edge * curEdge = vert[vert1].edge;
		if (curEdge)
		{
			if (curEdge->index == vert2)
			{
				vert[vert1].edge = curEdge->next;
				return true;
			}
			else{
				while (curEdge->next)
				{
					Edge * lastOfcurEdge = curEdge;
					curEdge = curEdge->next;
					if (curEdge->index == vert2)
					{
						lastOfcurEdge->next = curEdge->next;
						return true;
					}
				}
			}
		}
		else { return false; }
	};

	void Dijkstra()
	{
		
		for (;;)
		{	
			int vert1 = -1;

			for (int i = 0; i < numVert; i++)
			{
				if (table[i].known == false)
				{
					vert1 = i;
					break;
				}
			}
			for (int i = 0; i < numVert; i++)
			{
				if (table[i].known == false)
				{
					if (table[i].dist < table[vert1].dist)
					{
						vert1 = i;
					}
				}
			}
			if (vert1 == -1){ break; }

			table[vert1].known = true;
			Edge * curEdge = table[vert1].adjacency;
			while (curEdge)
			{
				if (!table[curEdge->index].known)
				{
					if (table[vert1].dist + curEdge->weight < table[curEdge->index].dist)
					{
						table[curEdge->index].dist = table[vert1].dist + curEdge->weight;
						table[curEdge->index].pathIndex = vert1;
					}
				}
				curEdge = curEdge->next;
			}
		}
	};

	/*
	* Dijkstra算法初始化表
	* @param int startindex 初始化顶点序号
	*/
	void initTable(int startindex)
	{
		table = new TableEntry[numVert];
		for (int i = 0; i < numVert; i++)
		{
			table[i].adjacency = getAdjacency(i);
			table[i].known = false;
			table[i].dist = INT_MAX;
			table[i].pathIndex = NOTAVERTEX;
		}
		table[startindex].dist = 0;
	};

	/*
	* 最短路径
	* @param int startindex 起始顶点
	*        int endindex 终止顶点
	*/
	bool shortestPath(int startindex,int endindex)
	{
		this->initTable(startindex);
		this->Dijkstra();
		this->printShortestPath(endindex);
		return true;
	};

	/*
	* 最小树生成
	*/
	bool minimalTree()
	{
		this->initTable(0);
		this->Dijkstra();
		this->printMinTree();
		return true;
	};
	
	/*
	* 输出Dijkstra算法辅助表
	*/
	void printTable()
	{
		for (int i = 0; i < numVert; i++)
		{
			printf("%d,%d,%d", table[i].known, table[i].dist, table[i].pathIndex);
			printf("\n");	
		}
	};

	/*
	* 输出最短路径
	*/
	void printShortestPath(int endindex)
	{
		if ((table[endindex].pathIndex) != -1)
		{
			this->printShortestPath(table[endindex].pathIndex);
			printf("to");
		}
		printf("%d", endindex);
	};

	/*
	* 输出最小树
	*/
	void printMinTree()
	{
		for (int i = 0; i < numVert; i++)
		{
			if (table[i].pathIndex != -1)
			{
				printf("%d-%d,%d", i,table[i].pathIndex,table[i].dist);
				printf("\n");
			}	
		}
	};

	/* 
	* 输出图
	*/
	void printGraph()
	{
		for (int i = 0; i < numVert; i++)
		{
			printf("[");
			if (vert[i].value != NULL)
			{
				printf("(%d,val:%d)", vert[i].index, vert[i].value);
			}
			printf("(");
			Edge * curEdge = vert[i].edge;
			while (curEdge)
			{
				printf("[%d,weight:%d]", curEdge->index, curEdge->weight);
				curEdge = curEdge->next;
			}
			printf(")");
			printf("]\n");
		}
	};
};
