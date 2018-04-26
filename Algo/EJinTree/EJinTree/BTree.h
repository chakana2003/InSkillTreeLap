#pragma once

class BTreeNode {
public:
	BTreeNode * Left;
	BTreeNode* Right;
	int Data;
public:
	BTreeNode();
	BTreeNode(int Value);
	void MakeLeftChild();
	void MakeLeftChild(int Value);
	void MakeRightChild();
	void MakeRightChild(int Value);
};

class BTree {
public:
	BTreeNode * Root;
public:
	BTree(int Value);
	void PreorderSearch(BTreeNode* Node);
	void InorderSearch(BTreeNode* Node);
	void PostorderSearch(BTreeNode* Node);
};