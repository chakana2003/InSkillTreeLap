#include "stdafx.h"
#include "BTree.h"
#include <iostream>

BTree::BTree(int Value)
{
	Root = new BTreeNode();
	Root->Data = Value;
}

void BTree::PreorderSearch(BTreeNode* Node)
{
	if (Node == NULL) {
		return;
	}

	std::cout << Node->Data << " ";
	PreorderSearch(Node->Right);
	PreorderSearch(Node->Left);
}

void BTree::InorderSearch(BTreeNode* Node)
{
	if (Node == NULL) {
		return;
	}
	InorderSearch(Node->Left);
	std::cout << Node->Data << " ";
	InorderSearch(Node->Right);
}

void BTree::PostorderSearch(BTreeNode* Node)
{
	if (Node == NULL) {
		return;
	}
	PostorderSearch(Node->Left);
	PostorderSearch(Node->Right);
	std::cout << Node->Data << " ";
}

BTreeNode::BTreeNode()
{
	Data = 0;
}

BTreeNode::BTreeNode(int Value)
{
	Data = Value;
}

void BTreeNode::MakeLeftChild()
{
	Left = new BTreeNode();
	Left->Data = 0;
}

void BTreeNode::MakeLeftChild(int Value)
{
	Left = new BTreeNode();
	Left->Data = Value;
}

void BTreeNode::MakeRightChild()
{
	Right = new BTreeNode();
	Right->Data = 0;
}

void BTreeNode::MakeRightChild(int Value)
{
	Right = new BTreeNode();
	Right->Data = Value;
}
