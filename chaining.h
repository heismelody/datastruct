#include "stdafx.h"
#include <iostream>
//#define MAXSIZE 10;
using namespace std;

template<class Type> class Chaining{

private:
	//散列表冲突链接的节点
	struct node
	{
		char * key;
		Type value;
		struct node * next;
	};
	//散列表大小
	int tablesize;
	//散列表
	node * hashtable;

public:

	/*
	* 构造函数，初始化散列表大小和散列表。
	*/
	Chaining()
	{
		this->tablesize = MAXSIZE;
		this->hashtable = new node[this->tablesize];
		for (int i = 0; i < tablesize; i++)
		{
			hashtable[i].key = NULL;
			hashtable[i].value = NULL;
			hashtable[i].next = NULL;
		}			 
	};

	/*
	* 散列函数
	* @param key
	* @return uint 散列值
	*/
	unsigned int hashFunction(char * key)
	{
		unsigned int h = 0;
		for (; *key; key++)
		{
			h = *key + h * 31;
		}	 

		return h%(this->tablesize);
	};

	/*
	* 散列过程，插入键值对
	* @param key，value
	* @return bool 散列过程是否成功
	*/
	bool hash(char *insertkey,Type insertvalue)
	{
		unsigned int h = this->hashFunction(insertkey);
		//解决key重复
		if (this->hasKey(insertkey)){ return false; }
		else 
		{
			node * newNode = new node();
			newNode->key = insertkey;
			newNode->value = insertvalue;
			newNode->next = NULL;
			if (hashtable[h].next == NULL)
			{
				hashtable[h].next = newNode;

				return true;
			}
			else
			{
				node * nextNode = hashtable[h].next;
				node * newNode = new node();
				newNode->key = insertkey;
				newNode->value = insertvalue;
				newNode->next = NULL;

				while (nextNode->next)
				{
					nextNode = nextNode->next;
				}
				nextNode->next = newNode;
				newNode->next = NULL;

				return true;
			}
		}
	};

	/*
	* key是否重复
	* @param key
	* @return bool key是否重复
	*/
	bool hasKey(char * key)
	{
		unsigned int h = this->hashFunction(key);
		node * curNode = &hashtable[h];

		while (curNode->next)
		{
			curNode = curNode->next;
			if (curNode->key == key){ return true; }
		}
		return false;
	};

	/*
	* 根据key获取value
	* @param key
	* @return Type key是否重复
	*/
	Type getValue(char * key)
	{
		unsigned int h = this->hashFunction(key);
		node * curNode = &hashtable[h];

		while (curNode->next)
		{
			curNode = curNode->next;
			if (curNode->key == key){ return curNode->value;}
		}
	};

	/*
	* 打印散列表
	*/
	void printTable()
	{
		for (int i = 0; i < this->tablesize; i++)
		{
			if (hashtable[i].next != NULL)
			{
				node * curNode = &hashtable[i];

				printf("(");
				while(curNode->next)
				{
					curNode = curNode->next;
					printf("%s%d,", curNode->key, curNode->value);
					
				}
				printf(")");
				printf("\n");
			}
			else
			{
				printf("()\n");
			}
		}
	};

};