#pragma once

class Single_Node {
public:
	int Value;
	Single_Node* Next;
};

class Single_List {
public:
	Single_Node* Head;
public:
	Single_List();
	void AddNode(int NewValue);
	void PrintNodes();
	Single_Node* SearchEnd();
};

class Double_Node {
public:
	int Value;
	Double_Node* Prev;
	Double_Node* Next;
};

class Double_List {
public:
	Double_Node * Head;
	Double_Node * Tail;
public:
	Double_List();
	void AddTail(int NewValue);
	void PrintFTail();
	void DeleteTail();
	void DeleteHead();
};

class Line {
public:
	char Text[100];
};

class View_Node {
public:
	Line Text;
	View_Node* Prev;
	View_Node* Next;
};

class View_List {
public:
	int Count;
	View_Node * Head;
	View_Node * Tail;
public:
	View_List();
	void AddTail(Line NewText);
	View_Node* IndexOf(int Index);
};

class DL_Stack {
public:
	Double_List Data;
public:
	void Push(int Value);
	int Pop();
	int Top();
};

class DL_Queue {
public:
	Double_List Data;
public:
	void Push(int Value);
	int Pop();
	int Top();
};

class Pos {
public:
	int y;
	int x;
public:
	Pos* FindPossible(int maze[10][10]);
};

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

void Prom_1_2();
void Prom_3();
void Prom_4();
void Prom_5();
void Prom_6();
void Prom_7();
void Prom_8();
void Prom_9();
void Prom_10();
void Prom_11();
void Prom_12();
void Prom_13();
void Prom_14();
void Prom_15();
void Prom_16();
void Prom_17();
void Prom_18();
void Prom_19();
void Prom_20();