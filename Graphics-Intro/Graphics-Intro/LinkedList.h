#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
struct LinkedNode
{
	T data;
	LinkedNode<T>* nextNode;

	//constructor
	LinkedNode(T value) : data(value), nextNode(nullptr) {}
};

template <typename T>
class LinkedList
{
public:
	//constructor
	LinkedList() : head(nullptr) {}
	
	LinkedNode<T>* MakeNode(LinkedNode<T>** head, T data);
	void InsertFirst(LinkedNode<T>** head, T data);
	void InsertAfter(LinkedNode<T>* lastNode, T data);
	void Append(LinkedNode<T>* head, T data);
	void DeleteList(LinkedNode<T>** node);
	void DeleteAfter(LinkedNode<T>* node);
	void DeleteNode(LinkedNode<T>* node, int pos);
	LinkedNode<T>* GetNode(LinkedNode<T>* node, int pos);
	LinkedNode<T>* Find(LinkedNode<T>* node, T value);
	int FindPosition(LinkedNode<T>* node, T value);
	int GetListSize(LinkedNode<T>* node);
	void PrintList(LinkedNode<T>* node);
	void PrintListBackwards(LinkedNode<T>* node);

private:
	LinkedNode<T>* head;
};

template <typename T>
LinkedNode<T>* LinkedList<T>::MakeNode(LinkedNode<T>** head, T data)
{
	LinkedNode<T>* newNode = new LinkedNode<T>(data);
	LinkedNode<T>* lastNode = *head;
	newNode->nextNode = nullptr;

	//if the head doesn't contain a node, create a head node for the start of the list
	if (*head == nullptr)
	{
		*head = newNode;
		return newNode;
	}

	//find the next node that doesn't point to a new node
	//then add this newly made node as their new node
	while (lastNode->nextNode != nullptr)
	{
		lastNode = lastNode->nextNode;
	}

	//set the last node in the list as the new node
	lastNode->nextNode = newNode;
	return newNode;
}

//<summary>
// insert a new node at the beginning of the linked list
//</summary>
template <typename T>
void LinkedList<T>::InsertFirst(LinkedNode<T>** head, T data)
{
	LinkedNode<T>* newNode = new LinkedNode<T>(data);

	//make the newNode the head of the list
	//and make the current head the nextNode of the newNode
	newNode->nextNode = *head;
	*head = newNode;
}

//<summary>
// insert a new node in the list after the referenced node
//</summary>
template <typename T>
void LinkedList<T>::InsertAfter(LinkedNode<T>* lastNode, T data)
{
	if (lastNode == nullptr)
	{
		cerr << "Last node cannot be null\n";
		return;
	}

	//make new node
	LinkedNode<T>* newNode = new LinkedNode<T>(data);
	newNode->data = data;

	//insert newNode by swapping the nextNode of the lastNode to be this newNode
	newNode->nextNode = lastNode->nextNode;
	lastNode->nextNode = newNode;
}

//<summary>
// add a new node only to the end of the list
//</summary>
template <typename T>
void LinkedList<T>::Append(LinkedNode<T>* node, T data)
{
	//make new node
	LinkedNode<T>* newNode = new LinkedNode<T>(data);
	newNode->nextNode = nullptr;
	newNode->data = data;

	while (node->nextNode != nullptr)
	{
		node = node->nextNode;
	}

	node->nextNode = newNode;
}

//<summary>
// delete every node in list then set the list to nullptr
//</summary>
template <typename T>
void LinkedList<T>::DeleteList(LinkedNode<T>** node)
{
	LinkedNode<T>* tempNode = *node;
	LinkedNode<T>* nextNode;

	//continue looping until it runs out of nodes
	while (tempNode != nullptr)
	{
		nextNode = tempNode->nextNode;
		delete tempNode;
		tempNode = nextNode;
	}

	*node = nullptr;
	cout << "List deleted\n";
}

//<summary>
// delete the node after the node referenced
//</summary>
template <typename T>
void LinkedList<T>::DeleteAfter(LinkedNode<T>* node)
{
	LinkedNode<T>* tempNode;
	if (node != nullptr && node->nextNode != nullptr)
	{
		tempNode = node->nextNode;
		node->nextNode = tempNode->nextNode;
		delete tempNode;
	}
}

//<summary>
// delete a node at a specific position
//</summary>
template <typename T>
void LinkedList<T>::DeleteNode(LinkedNode<T>* node, int pos)
{
	int count = 0;
	LinkedNode<T>* tempNode;

	while (node != nullptr)
	{
		//if the position to be deleted is the first
		if (pos == 0 && count == pos)
		{
			tempNode = node->nextNode;
			node->data = tempNode->data;
			node->nextNode = tempNode->nextNode;
			delete tempNode;
			cout << "Deleted node at position " << pos << endl;
			return;
		}
		else if (count == pos - 1)
		{
			tempNode = node->nextNode;

			if (tempNode->nextNode != nullptr)
				node->nextNode = tempNode->nextNode;
			else
				node->nextNode = nullptr;

			delete tempNode;

			cout << "Deleted node at position " << pos << endl;
			return;
		}

		count++;
		node = node->nextNode;
	}

	cerr << pos << " was not a valid position\n";
}

//<summary>
// get a node at the position referenced
//</summary>
template <typename T>
LinkedNode<T>* LinkedList<T>::GetNode(LinkedNode<T>* node, int pos)
{
	int count = 0;

	while (node != nullptr)
	{
		if (count == pos)
		{
			cout << "Data stored at position " << pos << " is: " << node->data << endl;
			return node;
		}

		count++;
		node = node->nextNode;
	}

	cerr << pos << " was not a valid position\n";
	return nullptr;
}

//<summary>
// finds a node based on referenced value
//</summary>
template <typename T>
LinkedNode<T>* LinkedList<T>::Find(LinkedNode<T>* node, T value)
{
	int count = 0;

	while (node != nullptr)
	{
		if (node->data == value)
		{
			cout << value << " is in the list, at position " << count << endl;
			return node;
		}

		count++;
		node = node->nextNode;
	}

	cerr << value << " is not in the list\n";
	return nullptr;
}

template<typename T>
inline int LinkedList<T>::FindPosition(LinkedNode<T>* node, T value)
{
	int count = 0;

	while (node != nullptr)
	{
		if (node->data == value)
		{
			cout << value << " is in the list, at position " << count << endl;
			return count;
		}

		count++;
		node = node->nextNode;
	}

	cerr << value << " is not in the list\n";
	return -1;
}

//<summary>
// go through whole list and return count
//</summary>
template<typename T>
inline int LinkedList<T>::GetListSize(LinkedNode<T>* node)
{
	int count = 0;

	while (node != nullptr)
	{
		count++;
		node = node->nextNode;
	}

	return count;
}

template <typename T>
void LinkedList<T>::PrintList(LinkedNode<T>* node)
{
	//while the node is set, print the data
	while (node != nullptr)
	{
		cout << setw(5) << "| " << node->data << " |-->";
		node = node->nextNode;
	}

	//if the head of list is not set, print null
	if (node == nullptr)
	{
		cout << "| NULL |" << endl;
	}

	cout << endl;
}

template <typename T>
void LinkedList<T>::PrintListBackwards(LinkedNode<T>* node)
{
	if (node != nullptr)
	{
		PrintListBackwards(node->nextNode);
		cout << setw(5) << "| " << node->data << " | -- >";
	}
}