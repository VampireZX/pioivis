#pragma once
#ifndef RBT_H_
#define RBT_H_
#include <iostream>

struct Node {
	int data;
	Node* parent;
	Node* left;
	Node* right;
	int color; // 1 - красный, 0 - черный
};
typedef Node* NodePtr;

class RBTree {
private:

	NodePtr searchTreeHelper(NodePtr node, int key);
	void fixDelete(NodePtr x);
	void rbTransplant(NodePtr u, NodePtr v);
	NodePtr minimum(NodePtr node);
	NodePtr maximum(NodePtr node);
	void deleteNodeHelper(NodePtr node, int key);
	void fixInsert(NodePtr k);

public:
	NodePtr root;
	NodePtr TNULL;

	RBTree();
	NodePtr searchTree(int k);
	int globalMinimum();
	int globalMaximum();
	void leftRotate(NodePtr x);
	int closestLesser(int k);
	void rightRotate(NodePtr x);
	void insert(int key);
	void deleteNode(int data);
};

#endif // !RBT_H_
