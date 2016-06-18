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

	//Dijkstra�㷨��ʹ�õĸ���������
	//�����ݽṹ���㷨����--C����������
	struct TableEntry          
	{
		Edge * adjacency;
		bool known;
		WeightType dist;
		int pathIndex;
	};
	TableEntry * table;

	Vert * vert;					//��ṹ������
	int numEdge;					//����
	int numEdgeOfEachVert;          //ÿ������ı���
	int numVert;					//������
	int maxsize;
	bool is_dir;                    //�Ƿ�Ϊ����ͼ,trueΪ����ͼ

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
	* ��ȡͼ�Ķ������
	* @param ��
	* @return int �������
	*/
	int getVert(){ return this->numVert; }					
	
	/* 
	* ��ȡͼ�ı���
	* @param ��
	* @return int ����
	*/
	int getEdge(){ return numEdge; }							
	
	/* 
	* ���ض��������ֵ
	* @param int index(���������е����)
	* @return ValueType value
	*/
	ValueType getValue(int index)
	{
		if (index < getVert() && this->vert[index].value){ return this->vert[index].value; }
		else { return NULL; }
	};

	/* 
	* ���ر��ϵ�Ȩֵ
	* @param int vert1 ����1��int vert2 ����2
	* @return Weight v1->v2�ߵ�Ȩ��
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
	*  ����index������ڽӶ���
	* @param int index(���������е����)
	* @return �߽ṹ�������ͷָ��
	*/
	Edge * getAdjacency(int index)
	{
		return vert[index].edge;
	};

	/* 
	* ���Ҷ����Ƿ����
	* @param int vert(���������е����)
	* @return true����
	*/
	bool isVertExist(int vert){ return vert < numVert ? true : false; };

	/* 
	* ����һ������
	* @param int insertindex ���붥������ 
	*        ValueType insertval ���붥���ֵ
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
	* ����һ������Ȩ�صı�
	* @param int vert1 ���Ϊ����ͼΪ��ʼ��, 
	*        int vert2 ���Ϊ����ͼΪ��ֹ��, 
	*        WeightType weight ��ʾȨ��
	* @return true ����ɹ�
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
	* ɾ��һ������
	* @param int index(���������е����)
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
	* ɾ��һ����
	* @param int vert1(����ͼ����ʼ���������е����)
	*        int vert2������ͼ����ֹ���������е���ţ� 
	* @return ����
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
	* Dijkstra�㷨��ʼ����
	* @param int startindex ��ʼ���������
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
	* ���·��
	* @param int startindex ��ʼ����
	*        int endindex ��ֹ����
	*/
	bool shortestPath(int startindex,int endindex)
	{
		this->initTable(startindex);
		this->Dijkstra();
		this->printShortestPath(endindex);
		return true;
	};

	/*
	* ��С������
	*/
	bool minimalTree()
	{
		this->initTable(0);
		this->Dijkstra();
		this->printMinTree();
		return true;
	};
	
	/*
	* ���Dijkstra�㷨������
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
	* ������·��
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
	* �����С��
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
	* ���ͼ
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
