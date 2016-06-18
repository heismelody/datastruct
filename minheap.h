#include "stdafx.h"
#include <iostream>
#define MAXSIZE 15;

using namespace std;
template<class Type> class MinHeap{

private:
	Type *heap;
	int size;
	int maxsize;

	bool isFull(){return size < maxsize ? false : true;};
	bool isEmpty(){ return size == 0 ? true : false; };
	int getSize(){ return this->size; }

	int leftsonOf(int index){ return index * 2 + 1; };
	int rightsonOf(int index){ return index * 2 + 2; };
	int parentOf(int index){ return (index - 1) / 2; };
	bool hasrightson(int index){ return index * 2 + 2 < this->size ? true : false; };
	bool hasson(int index){ return index * 2 + 1 < this->size ? true : false; };

	void swapNode(int node1,int node2)
	{
		Type temp = heap[node1];
		heap[node1] = heap[node2];
		heap[node2] = temp;
	};

	/*
	* 从给定节点向下调整堆
	* @param int downindex 调整节点的序号
	*/
	void heapDown(int downindex)
	{
		while (hasrightson(downindex) || hasson(downindex))
		{
			if (hasrightson(downindex))
			{
				if (heap[leftsonOf(downindex)] < heap[downindex] && heap[leftsonOf(downindex)] < heap[rightsonOf(downindex)])
				{
					swapNode(downindex, leftsonOf(downindex));
					downindex = leftsonOf(downindex);
				}
				else if (heap[rightsonOf(downindex)] < heap[downindex] && heap[rightsonOf(downindex)] < heap[leftsonOf(downindex)])
				{
					swapNode(downindex, rightsonOf(downindex));
					downindex = rightsonOf(downindex);
				}
				else { break; }
			}
			else
			{
				if (heap[downindex] > heap[leftsonOf(downindex)])
				{
					swapNode(downindex, leftsonOf(downindex));
					break;
				}
				else { break; }
			}
		}
	};
public:

	MinHeap(int size, Type data[]){
		this->size = size;
		this->maxsize = MAXSIZE;
		heap = new Type[this->maxsize];
		for (int i = 0; i < this->size; i++)
		{
			heap[i] = data[i];
		}
		this->initHeap();
	};

	/*
	* 初始化最小堆，使得堆符合最小堆的性质。
	*/
	void initHeap()
	{
		for (int i = (size - 1) / 2; i >= 0; i--)
		{
			this->heapDown(i);
		}
	}

	/*
	* 判断节点是否存在
	* @param Type node 节点值
	* @return true 存在
	*/
	bool isExist(Type node)
	{
		for (int i = 0; i < size; i++)
		{
			if (this->heap[i] == node){ return true; }
		}
		return false;
	};

	/*
	* 插入节点
	* @param Type node 插入节点的值
	* @return true 插入成功
	*/
	bool insertNode(Type node)
	{
		if(this->heap == NULL || size == 0)
		{
			this->size ++;
			heap[0] = node;
		}
		else if (!this->isFull())
		{
			if (this->isExist(node)){ return false; }
			else
			{
				this->size = this->size + 1;
				int i = this->size - 1;
				while(node < heap[parentOf(i)] && i != 0)
				{
					heap[i] = heap[parentOf(i)];
					i = parentOf(i);
				}
				heap[i] = node;
				return true;
			}
		}
		else
		{
			return false;
		}
	};

	/*
	* 删除节点
	* @param Type node 删除节点的值
	* @return true 成功删除
	*/
	bool removeNode(Type node)
	{
		if (!this->isEmpty())
		{
			this->size--;

			int indexOfRemove = findNodeIndex(node);
			heap[indexOfRemove] = heap[this->size];
			this->heapDown(indexOfRemove);

			return true;
		}
		else{ return false; }
	};

	/*
	* 查找结点在堆中的序号
	* @param Type node 查找节点的值
	* @return int i 结点的序号
	*		  -1  未查找到结点	
	*/
	int findNodeIndex(Type node)
	{
		int i = 0;
		while (i < this->size)
		{
			if (heap[i] == node){ return i; }
			i++;
		}
		return -1;
	}

	/*
	* 删除最小节点
	* @param
	* @return true 成功删除
	*/
	bool removeMin()
	{
		if (!this->isEmpty())
		{
			this->removeNode(this->heap[0]);
			return true;
		}
		else{ return false; }
		
	};

	/*
	* 获取最小结点的值
	* @param
	* @return Type 最小结点的值
	*/
	Type getMin(){ return this->heap[0]; };

	/*
	* 输出堆
	*/
	void printHeap(){
		int i = 0;
		while (i < this->size)
		{
			cout << this->heap[i];
			printf(",");
			i++;
		}
	};
};