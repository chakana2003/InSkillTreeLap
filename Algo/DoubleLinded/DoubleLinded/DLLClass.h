#pragma once

#include <stdio.h>
#include <stdlib.h>

// ���ø� Ȱ�� Ŭ����

template<typename T>
class DLLNode                    // ��� Ŭ����
{
public:
	T Value;
	DLLNode* Prev;
	DLLNode* Next;
};

template<typename T>
class DLList {                  // ����Ʈ Ŭ����
private:
	DLLNode<T>* Head;
	DLLNode<T>* Tail;
public:
	DLList();

	// ��� �߰��ϰ� ��ȯ
	DLLNode<T>* MakeNode(T Value);

	// ������ ��带 �߰��ϴ� �Լ�
	void AddNode(T Value);

	//�տ������� ���
	void PrintNodeFromHead();

	// �ڿ������� ���
	void PrintNodeFromTail();

	// Value �� ã�Ƽ� ����
	void DeleteNode(T Value);

	void InsertBefore(T SearchValue, T Value);

	void InsertAfter(T SearchValue, T Value);

	DLLNode<T>* Begin() { return Head->Next; }
	DLLNode<T>* End() { return Tail->Prev; }
};

template<typename T>
inline DLList<T>::DLList()
{
	Head = NULL;
	Tail = NULL;
}

template<typename T>
DLLNode<T>* DLList<T>::MakeNode(T Value) {
	// DLLNode<T>* Temp = (DLLNode<T>*)malloc(sizeof(DLLNode<T>));
	DLLNode<T>* Temp = new DLLNode<T>;
	Temp->Value = Value;
	Temp->Next = NULL;
	Temp->Prev = NULL;
	return Temp;
}

template<typename T>
void DLList<T>::AddNode(T Value) {       // ������ ��带 �߰��ϴ� �Լ�
	if (Head == NULL) {         // �� ó�� ���鶧
		Head = MakeNode(0);
		Tail = MakeNode(0);
		Head->Next = Tail;
		Tail->Prev = Head;

		DLLNode<T>* NewNode = MakeNode(Value);
		Head->Next = NewNode;
		NewNode->Prev = Head;
		Tail->Prev = NewNode;
		NewNode->Next = Tail;
	}
	else
	{                          // �� �������� ���鶧
		DLLNode<T>* NewNode = MakeNode(Value);

		Tail->Prev->Next = NewNode;
		NewNode->Next = Tail;
		NewNode->Prev = Tail->Prev;
		Tail->Prev = NewNode;

	}
}

template<typename T>
void DLList<T>::PrintNodeFromHead() {
	printf("---------------------\n");
	for (DLLNode<T>* Current = Head->Next; Current != NULL; Current = Current->Next) {
		if (Current != Tail) {
			printf("%d\n", Current->Value);
		}
	}
}

template<typename T>
void DLList<T>::PrintNodeFromTail() {
	printf("---------------------\n");
	for (DLLNode<T>* Current = Tail->Prev; Current != NULL; Current = Current->Prev) {
		if (Current != Head) {
			printf("%d\n", Current->Value);
		}
	}
}

template<typename T>
void DLList<T>::DeleteNode(T Value) {
	for (DLLNode<T>* Current = Head->Next; Current != Tail; Current = Current->Next) {
		if (Current->Value == Value) {
			Current->Prev->Next = Current->Next;    // ã������� �ճ���� ������带 ã������� �������� ����
			Current->Next->Prev = Current->Prev;    // ã������� ��������� �ճ�带 ã������� �ճ��� ����
			free(Current);                          // �ع�
			return;
		}
	}
}

template<typename T>
void DLList<T>::InsertBefore(T SearchValue, T Value) {
	for (DLLNode<T>* Current = Head->Next; Current != Tail; Current = Current->Next) {
		if (Current->Value == SearchValue) {
			DLLNode<T>* NewNode = MakeNode(Value);
			Current->Prev->Next = NewNode;
			NewNode->Prev = Current->Prev;
			NewNode->Next = Current;
			Current->Prev = NewNode;
		}
	}
}

template<typename T>
void DLList<T>::InsertAfter(T SearchValue, T Value)
{
	for (DLLNode<T>* Current = Head->Next; Current != Tail; Current = Current->Next) {
		if (Current->Value == SearchValue) {
			DLLNode<T>* NewNode = MakeNode(Value);

			Current->Next->Prev = NewNode;
			NewNode->Next = Current->Next;
			Current->Next = NewNode;
			NewNode->Prev = Current;
		}
	}
}
