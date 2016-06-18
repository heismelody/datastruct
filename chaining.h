#include "stdafx.h"
#include <iostream>
//#define MAXSIZE 10;
using namespace std;

template<class Type> class Chaining{

private:
	//ɢ�б��ͻ���ӵĽڵ�
	struct node
	{
		char * key;
		Type value;
		struct node * next;
	};
	//ɢ�б��С
	int tablesize;
	//ɢ�б�
	node * hashtable;

public:

	/*
	* ���캯������ʼ��ɢ�б��С��ɢ�б�
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
	* ɢ�к���
	* @param key
	* @return uint ɢ��ֵ
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
	* ɢ�й��̣������ֵ��
	* @param key��value
	* @return bool ɢ�й����Ƿ�ɹ�
	*/
	bool hash(char *insertkey,Type insertvalue)
	{
		unsigned int h = this->hashFunction(insertkey);
		//���key�ظ�
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
	* key�Ƿ��ظ�
	* @param key
	* @return bool key�Ƿ��ظ�
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
	* ����key��ȡvalue
	* @param key
	* @return Type key�Ƿ��ظ�
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
	* ��ӡɢ�б�
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