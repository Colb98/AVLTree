#pragma once

class Node {
public:
	int key;
	Node* left;
	Node* right;
	Node* parent;

	Node(int k);
};

class Tree
{
private:
	Node* root;

	Node* Insert(int k, Node*& r);
	void BalanceAtNode(Node *& r);
	// Height of tree has root is this node
	int Height(Node *r);
	int Weight(Node *r);
	// Depth of this node in the tree
	int DepthOfNode(Node *r);
	void Draw(Node *r);
	void FirstOrder(void(*f)(Node*), Node* p);
	void MidOrder(void(*f)(Node*), Node* p);
	void LastOrder(void(*f)(Node*), Node* p);
	void RightRotate(Node* p);
	void LeftRotate(Node* p);
	Node* RightMost(Node* p);
	Node* LeftMost(Node* p);
public:
	Tree();
	~Tree();
	Tree(int k);
	Tree(Node* r);
	void FirstOrder(void (*f)(Node*));
	void MidOrder(void (*f)(Node*));
	void LastOrder(void (*f)(Node*));
	Node* Insert(int k);
	Node* Find(int k);
	void Delete(int k);
	void Draw();
	int NumberOfNodes();
};

