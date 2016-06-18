#include "stdafx.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

template<class ValueType, class WeightType> class HuffTree{
private:
	struct Node
	{
		ValueType value;
		WeightType weight;
		string code;
		Node * leftson;
		Node * rightson;
	};
	Node * root;
	Node * hufftree;
	int curHuffTreeSize;
public:

	HuffTree(int size,ValueType *value,WeightType *weight)
	{
		root = NULL;
		curHuffTreeSize = size;
		hufftree = new Node[size];
		for (int i = 0; i < curHuffTreeSize; i++)
		{
			hufftree[i].code = "";
			hufftree[i].value = value[i];
			hufftree[i].weight = weight[i];
			hufftree[i].leftson = NULL;
			hufftree[i].rightson = NULL;
		}
	};

	Node * getRoot(){ return root; };

	void createHuffTree()
	{
		int size = curHuffTreeSize;
		while (size > 1)
		{
			int secLeastNode = 0;
			int leastNode = 0;
			for (int i = 0; i < curHuffTreeSize; i++)
			{
				if (hufftree[i].weight != NULL)
				{
					leastNode = i;
					break;
				}
			}
			for (int j = leastNode+1; j < curHuffTreeSize; j++)
			{
				if (hufftree[j].weight != NULL)
				{
					secLeastNode = j;
					break;
				}
			}
			if (hufftree[leastNode].weight > hufftree[secLeastNode].weight)
			{
				int temp = secLeastNode;
				secLeastNode = leastNode;
				leastNode = temp;
			}
			int i = 0;
			if (leastNode < secLeastNode){ i = secLeastNode; }
			else{ i = leastNode; }
			for (i = i+1; i < curHuffTreeSize; i++)
			{
				if (hufftree[i].weight != NULL)
				{
					if (hufftree[i].weight < hufftree[leastNode].weight)
					{
						secLeastNode = leastNode;
						leastNode = i;
					}
					else if (hufftree[i].weight < hufftree[secLeastNode].weight)
					{
						secLeastNode = i;
					}
				}
			}
			Node * newrightNode;
			Node * newleftNode; 
			newleftNode = new Node();
			newrightNode = new Node();

			newleftNode->value = hufftree[secLeastNode].value;
			newleftNode->weight = hufftree[secLeastNode].weight;
			newleftNode->leftson = hufftree[secLeastNode].leftson;
			newleftNode->rightson = hufftree[secLeastNode].rightson;

			newrightNode->value = hufftree[leastNode].value;
			newrightNode->weight = hufftree[leastNode].weight;
			newrightNode->leftson = hufftree[leastNode].leftson;
			newrightNode->rightson = hufftree[leastNode].rightson;

			hufftree[secLeastNode].weight = newleftNode->weight + newrightNode->weight;
			hufftree[secLeastNode].leftson = newleftNode;
			hufftree[secLeastNode].rightson = newrightNode;

			hufftree[leastNode].value = NULL;
			hufftree[leastNode].weight = NULL;
			root = &hufftree[secLeastNode];
			size--;
		}
	};

	void printHuffCode(Node *p)
	{
		queue<Node*> nq;
		nq.push(p);
		while (nq.size() != 0)
		{
			Node* cur = nq.front();
			nq.pop();
			Node* l = cur->leftson;
			if (l != NULL)
			{
				l->code = cur->code + "0";
				nq.push(l);
			}
			Node* r = cur->rightson;
			if (r != NULL)
			{
				r->code = cur->code + "1";
				nq.push(r);
			}
			if (l == NULL&&r == NULL)
			{
				cout << cur->weight << ": " << cur->code << endl;
			}
		}
	};

	void printHuffTree(Node *p)
	{
		if (p)
		{
			printf("(%d,%d)", p->value, p->weight);
			printHuffTree(p->leftson);
			printHuffTree(p->rightson);
		}
	};
};