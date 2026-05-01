#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

struct LinkedNode
{
	int data;
	LinkedNode* nextNode;
};

class LinkedList
{
public:
	LinkedNode* head = nullptr;
	
	LinkedList();
	~LinkedList();

	LinkedNode* MakeNode(LinkedNode** head, int data);
	LinkedNode* InsertFirst(LinkedNode** head, int data);
	void InsertAfter(LinkedNode* lastNode, int data);
	void Append(LinkedNode* head, int data);
	void DeleteList(LinkedNode** node);
	void DeleteAfter(LinkedNode* node);
	void DeleteNode(LinkedNode* node, int pos);
	LinkedNode* GetNode(LinkedNode* node, int pos);
	LinkedNode* Find(LinkedNode* node, int value);
	void PrintList(LinkedNode* node);
	void PrintListBackwards(LinkedNode* node);
};

