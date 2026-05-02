#pragma once
#include <iostream>
#include <queue>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* leftNode;
	TreeNode<T>* rightNode;

	//constructor
	TreeNode(T value) : data(value), leftNode(nullptr), rightNode(nullptr) {}
};

template <typename T>
class BinaryTree
{
public:
	BinaryTree() : head(nullptr) {}
	
	TreeNode<T>* MakeHead(TreeNode<T>** head, T data);
	void PrintPreOrder(TreeNode<T>* node);
	void PrintInOrder(TreeNode<T>* node);
	void PrintPostOrder(TreeNode<T>* node);
	TreeNode<T>* DepthSearch(TreeNode<T>* node, T data);
	TreeNode<T>* BreadthSearch(TreeNode<T>* node, T data);
	void DeleteTree(TreeNode<T>** head);
	void DeleteAfter(TreeNode<T>** node, bool right);
	void InsertFirst(TreeNode<T>** head, T data);
	void InsertAfter(TreeNode<T>* lastNode, T data, bool right);
	void InsertLeft(TreeNode<T>* lastNode, TreeNode<T>* newNode);
	void InsertRight(TreeNode<T>* lastNode, TreeNode<T>* newNode);

private:
	TreeNode<T>* head;
	void PrintTree(TreeNode<T>* node);
};

template<typename T>
inline TreeNode<T>* BinaryTree<T>::MakeHead(TreeNode<T>** head, T data)
{
	TreeNode<T>* newNode = new TreeNode<T>(data);
	newNode->data = data;
	newNode->leftNode = nullptr;
	newNode->rightNode = nullptr;

	//if the head doesn't contain a node, create a head node for the start of the list
	if (*head == nullptr)
	{
		*head = newNode;
		return newNode;
	}
}

template<typename T>
void BinaryTree<T>::PrintPreOrder(TreeNode<T>* node)
{
	PrintTree(node);
	if (node == nullptr)
		return;

	if (node->leftNode != nullptr)
	{

		cout << "parent node: " << node->data << endl;
		cout << "left node: ";
		PrintPreOrder(node->leftNode);
	}
	if (node->rightNode != nullptr)
	{

		cout << "parent node: " << node->data << endl;
		cout << "right node: ";
		PrintPreOrder(node->rightNode);
	}
}

template<typename T>
void BinaryTree<T>::PrintInOrder(TreeNode<T>* node)
{
	if (node == nullptr)
		return;

	if (node->leftNode != nullptr)
	{
		cout << "left node: ";
		PrintInOrder(node->leftNode);
	}
	PrintTree(node);
	if (node->rightNode != nullptr)
	{
		cout << "right node: ";
		PrintInOrder(node->rightNode);
	}
}

template<typename T>
void BinaryTree<T>::PrintPostOrder(TreeNode<T>* node)
{
	if (node == nullptr)
		return;

	if (node->leftNode != nullptr)
	{
		cout << "left node: ";
		PrintPostOrder(node->leftNode);
	}
	if (node->rightNode != nullptr)
	{
		cout << "right node: ";
		PrintPostOrder(node->rightNode);
	}
	PrintTree(node);
}


//<summary>
// returns pointer to the node containing the desired data if found
// searches fully down one branch before searching down the next branch
//</summary>
template<typename T>
TreeNode<T>* BinaryTree<T>::DepthSearch(TreeNode<T>* node, T data)
{
	TreeNode<T>* answer = nullptr;
	PrintTree(node);

	if (node->data == data)
		return node;
	if (node->leftNode != nullptr)
		answer = DepthSearch(node->leftNode, data);
	if (node->rightNode != nullptr)
		answer = DepthSearch(node->rightNode, data);

	return answer;
}

template<typename T>
TreeNode<T>* BinaryTree<T>::BreadthSearch(TreeNode<T>* node, T data)
{
	TreeNode<T>* answer = nullptr;
	queue<TreeNode<T>*> queue;
	queue.push(node);

	while (!queue.empty())
	{
		TreeNode<T>* current = queue.front();
		queue.pop();

		if (current->data == data)
			return current;

		if (current->leftNode != nullptr)
			queue.push(current->leftNode);

		if (current->rightNode != nullptr)
			queue.push(current->rightNode);
	}

	return answer;
}

template<typename T>
void BinaryTree<T>::DeleteTree(TreeNode<T>** head)
{
	if (head == nullptr || *head == nullptr)
		return;
	
	if ((*head)->leftNode != nullptr)
		DeleteTree(&((*head)->leftNode));
	if ((*head)->rightNode != nullptr)
		DeleteTree(&((*head)->rightNode));

	cout << "Deleting node" << endl;
	delete* head;
	*head = nullptr;
}

//<summary>
// delete the leaf nodes on the end of the tree
//</summary>
template<typename T>
void BinaryTree<T>::DeleteAfter(TreeNode<T>** node, bool right)
{
	if (node == nullptr || *node == nullptr)
	{
		cerr << "There are no nodes to delete after that node\n";
		return;
	}
	
	if (right && (*node)->rightNode != nullptr && (*node)->rightNode->leftNode == nullptr && (*node)->rightNode->rightNode == nullptr)
	{
		delete (*node)->rightNode;
		(*node)->rightNode = nullptr;
	}
	else if (!right && (*node)->leftNode != nullptr && (*node)->leftNode->leftNode == nullptr && (*node)->leftNode->rightNode == nullptr)
	{
		delete (*node)->leftNode;
		(*node)->leftNode = nullptr;
	}
}

template<typename T>
void BinaryTree<T>::InsertFirst(TreeNode<T>** head, T data)
{
	TreeNode<T>* newNode = new TreeNode<T>(data);
	newNode->data = data;

	//assign the child node of the newNode as the previous head node
	newNode->leftNode = *head;

	//set the head node to be the newNode
	*head = newNode;
}

template<typename T>
void BinaryTree<T>::InsertAfter(TreeNode<T>* lastNode, T data, bool right)
{
	if (lastNode == nullptr)
	{
		cerr << "Last node cannot be null\n";
		return;
	}

	//make new node
	TreeNode<T>* newNode = new TreeNode<T>(data);
	newNode->data = data;

	//set new node with the same node refs as the lastNode
	newNode->leftNode = nullptr;
	newNode->rightNode = nullptr;

	if (right)
		InsertRight(lastNode, newNode);
	else
		InsertLeft(lastNode, newNode);
}

template<typename T>
void BinaryTree<T>::InsertLeft(TreeNode<T>* lastNode, TreeNode<T>* newNode)
{
	if (lastNode == nullptr)
	{
		cerr << "Last node cannot be null\n";
		return;
	}

	newNode->leftNode = lastNode->leftNode;
	lastNode->leftNode = newNode;
}

template<typename T>
void BinaryTree<T>::InsertRight(TreeNode<T>* lastNode, TreeNode<T>* newNode)
{
	if (lastNode == nullptr)
	{
		cerr << "Last node cannot be null\n";
		return;
	}

	newNode->rightNode = lastNode->rightNode;
	lastNode->rightNode = newNode;
}

template<typename T>
void BinaryTree<T>::PrintTree(TreeNode<T>* node)
{
	if (node != nullptr)
		cout << node->data << endl;
	else
		cout << "NULL" << endl;
}
