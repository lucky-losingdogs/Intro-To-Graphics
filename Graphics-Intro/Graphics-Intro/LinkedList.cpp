#include "LinkedList.h"

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
}

LinkedNode* LinkedList::MakeNode(LinkedNode** head, int data)
{
	LinkedNode* newNode = new LinkedNode;
	LinkedNode* lastNode = *head;

	newNode->data = data;
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
LinkedNode* LinkedList::InsertFirst(LinkedNode** head, int data)
{
	LinkedNode* newNode = new LinkedNode;
	//assign data
	newNode->data = data;

	//make the newNode the head of the list
	//and make the current head the nextNode of the newNode
	newNode->nextNode = *head;
	*head = newNode;

	return newNode;
}

//<summary>
// insert a new node in the list after the referenced node
//</summary>
void LinkedList::InsertAfter(LinkedNode* lastNode, int data)
{
	if (lastNode == nullptr)
	{
		cerr << "Last node cannot be null\n";
		return;
	}
	
	//make new node
	LinkedNode* newNode = new LinkedNode;
	newNode->data = data;

	//inset newNode by swapping the nextNode of the lastNode to be this newNode
	newNode->nextNode = lastNode->nextNode;
	lastNode->nextNode = newNode;
}

void LinkedList::Append(LinkedNode* node, int data)
{
	//make new node
	LinkedNode* newNode = new LinkedNode;
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
void LinkedList::DeleteList(LinkedNode** node)
{
	LinkedNode* tempNode = *node;
	LinkedNode* nextNode;

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
void LinkedList::DeleteAfter(LinkedNode* node)
{
	LinkedNode* tempNode;
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
void LinkedList::DeleteNode(LinkedNode* node, int pos)
{
	int count = 0;
	LinkedNode* tempNode;

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
LinkedNode* LinkedList::GetNode(LinkedNode* node, int pos)
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
LinkedNode* LinkedList::Find(LinkedNode* node, int value)
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

void LinkedList::PrintList(LinkedNode* node)
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

void LinkedList::PrintListBackwards(LinkedNode* node)
{
	if (node != nullptr)
	{
		PrintListBackwards(node->nextNode);
		cout << setw(5) << "| " << node->data << " | -- >";
	}
}