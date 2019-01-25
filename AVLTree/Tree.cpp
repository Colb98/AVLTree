#include "Tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

bool isLeft(Node* p);

Node::Node(int k) {
	key = k;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}


Tree::Tree()
{
	root = nullptr;
}


Tree::~Tree()
{
	//Free all
}

Tree::Tree(int k) {
	root = new Node(k);
}

Tree::Tree(Node *r) {
	root = r;
}

void Tree::FirstOrder(void(*f)(Node*)) {
	FirstOrder(f, root);
}

void Tree::MidOrder(void(*f)(Node*)) {
	MidOrder(f, root);
}

void Tree::LastOrder(void(*f)(Node*)) {
	LastOrder(f, root);
}

void Tree::FirstOrder(void(*f)(Node*), Node* p) {
	if (p == nullptr)
		return;
	f(p);
	FirstOrder(f, p->left);
	FirstOrder(f, p->right);
}

void Tree::MidOrder(void(*f)(Node*), Node* p) {
	if (p == nullptr)
		return;
	MidOrder(f, p->left);
	f(p);
	MidOrder(f, p->right);
}

void Tree::LastOrder(void(*f)(Node*), Node* p) {
	if (p == nullptr)
		return;
	LastOrder(f, p->left);
	LastOrder(f, p->right);
	f(p);
}

Node* Tree::Insert(int k) {
	if (root == nullptr)
		return root = new Node(k);
	else
		return Insert(k, root);
}

Node* Tree::Insert(int k, Node*& r) {
	if (r == nullptr) {
		r = new Node(k);
		return r;
	}
	
	if (k < r->key) {
		Node *p = Insert(k, r->left);
		if (r->left->parent != r)
			r->left->parent = r;

		BalanceAtNode(r);

		return p;
	}
	else if (k > r->key) {
		Node *p = Insert(k, r->right);
		if (r->right->parent != r)
			r->right->parent = r;

		BalanceAtNode(r);

		return p;
	}
	else
		return r;
}

void Tree::BalanceAtNode(Node *& r)
{
	if (Height(r->left) - 1 > Height(r->right))
		if (Height(r->left->left) > Height(r->left->right))
			// Left Left case
			RightRotate(r);
		else
			// Left Right case
		{
			LeftRotate(r->left);
			RightRotate(r);
		}
	else if (Height(r->right) - 1 > Height(r->left))
		if (Height(r->right->right) > Height(r->right->left))
			// Right Right case
			LeftRotate(r);
		else
			// Right Left case
		{
			RightRotate(r->right);
			LeftRotate(r);
		}
}

void Tree::Draw() {
	Draw(root);
	cout << "Number of nodes: " << NumberOfNodes();
	cout << endl << endl;
}

void Tree::Draw(Node* r) {
	if (r == nullptr)
		return;

	bool top = isLeft(r);
	// Mid order draw
	Draw(r->left);

	int d = DepthOfNode(r);
	// Space before this node key
	string space = d > 0 ? "   " : "";
	Node* p = r;
	while (p->parent != nullptr && p->parent->parent != nullptr) {
		// Left - Right or Right - Left
		if (isLeft(p) != isLeft(p->parent)) {
			space.insert(space.begin(), 179);
			space = "   " + space;
		}
		else
			space = "    " + space;
		p = p->parent;
	}

	cout << space;

	if (d > 0) {
		if (top)
			cout << ((char)218);
		else
			cout << ((char)192);
	}

	cout << setw(2) << r->key << ' ';

	if (r->left != nullptr && r->right != nullptr)
		cout << ((char)180);
	else if (r->left != nullptr)
		cout << ((char)217);
	else if (r->right != nullptr)
		cout << ((char)191);

	cout << endl;

	Draw(r->right);
}

int Tree::DepthOfNode(Node* r) {
	int depth = 0;
	Node* root = this->root;
	while (root->key != r->key) {
		depth++;
		if (r->key < root->key)
			root = root->left;
		else
			root = root->right;

		if (root == nullptr)
			return -1;
	}
	return depth;
}

bool isLeft(Node* p) {
	if (p->parent == nullptr)
		return false;
	if (p->parent->left == p)
		return true;
	return false;
}

int Tree::Height(Node* r) {
	if (r == nullptr)
		return 0;
	int hleft = Height(r->left);
	int hright = Height(r->right);
	return hleft > hright ? hleft + 1 : hright + 1;
}

void Tree::RightRotate(Node* p) {
	Node* q = p->left;
	Node* r = q->right;

	if (root == p)
		root = q;

	if (p->parent != nullptr)
		if (p->parent->left == p)
			p->parent->left = q;
		else
			p->parent->right = q;

	q->parent = p->parent;
	p->parent = q;
	q->right = p;
	if(r != nullptr)
		r->parent = p;
	p->left = r;
}

void Tree::LeftRotate(Node* p) {
	Node* q = p->right;
	Node* r = q->left;

	if (root == p)
		root = q;

	if (p->parent != nullptr)
		if (p->parent->left == p)
			p->parent->left = q;
		else
			p->parent->right = q;

	q->parent = p->parent;
	p->parent = q;
	q->left = p;
	if (r != nullptr)
		r->parent = p;
	p->right = r;
}

Node* Tree::Find(int k) {
	Node* p = root;
	while (p->key != k) {
		if (k < p->key)
			p = p->left;
		else
			p = p->right;
		if (p == nullptr)
			break;
	}
	return p;
}

Node* Tree::RightMost(Node* p) {
	if (p == nullptr || p->right == nullptr)
		return p;
	Node* q = p->right;
	while (q->right != nullptr)
		q = q->right;
	return q;
}

Node* Tree::LeftMost(Node* p) {
	if (p == nullptr || p->left == nullptr)
		return p;
	Node* q = p->left;
	while (q->left != nullptr)
		q = q->left;
	return q;
}

void Tree::Delete(int k) {
	Node* p = Find(k);
	if (p == nullptr)
		return;
	Node* parent = p->parent;
	if (p->left == nullptr && p->right == nullptr) {
		if (p->parent->left == p)
			p->parent->left = nullptr;
		else
			p->parent->right = nullptr;
		delete p;		
	}
	else if (p->left == nullptr)
	{
		Node* q = p->right;
		parent = q;
		if (p->parent->left == p)
			p->parent->left = q;
		else
			p->parent->right = q;
		q->parent = p->parent;
		delete p;
	}
	else {
		//p->left is not null in this case	
		Node* q = RightMost(p->left);

		//Check if q is the right child node (q can be p->left)
		if (q == p->left) {
			parent = q;
			q->right = p->right;
			if (q->right != nullptr)
				q->right->parent = q;
			q->parent = p->parent;
			if (p->parent->left == p)
				p->parent->left = q;
			else
				p->parent->right = q;
			delete p;
		}
		else {
			parent = q->parent;
			p->key = q->key;
			q->parent->right = q->left;
			if (q->left != nullptr)
				q->left->parent = q->parent;
			delete q;
		}
	}

	do {
		BalanceAtNode(parent);
		parent = parent->parent;
	} while (parent != nullptr);
}

int Tree::NumberOfNodes() {
	vector<Node*> stack;
	int count = 0;
	stack.insert(stack.begin(), root);
	while (stack.size() > 0) {
		Node* p = stack[0];
		if (p->left != nullptr)
			stack.push_back(p->left);
		if (p->right != nullptr)
			stack.push_back(p->right);
		stack.erase(stack.begin());
		count++;		
	}
	return count;
}