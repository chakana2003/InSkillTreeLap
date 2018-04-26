#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "DLList.h"

Node* Head = NULL;
Node* Tail = NULL;

Node* MakeNode(int Value) {
	Node* Temp = (Node*)malloc(sizeof(Node));
	Temp->Value = Value;
	Temp->Next = NULL;
	Temp->Prev = NULL;
	return Temp;
}

void AddNode(int Value) {       // ������ ��带 �߰��ϴ� �Լ�
	if (Head == NULL) {         // �� ó�� ���鶧
		Head = MakeNode(0);
		Tail = MakeNode(0);
		Head->Next = Tail;
		Tail->Prev = Head;

		Node* NewNode = MakeNode(Value);
		Head->Next = NewNode;
		NewNode->Prev = Head;
		Tail->Prev = NewNode;
		NewNode->Next = Tail;
	}
	else
	{                          // �� �������� ���鶧
		Node* NewNode = MakeNode(Value);

		Tail->Prev->Next = NewNode;
		NewNode->Next = Tail;
		NewNode->Prev = Tail->Prev;
		Tail->Prev = NewNode;
		
	}
}

void PrintNodeFromHead() {
	printf("---------------------\n");
	for (Node* Current = Head->Next; Current != NULL; Current = Current->Next) {
		if (Current != Tail) {
			printf("%d\n", Current->Value);
		}
	}
}

void PrintNodeFromTail() {
	printf("---------------------\n");
	for (Node* Current = Tail->Prev; Current != NULL; Current = Current->Prev) {
		if (Current != Head) {
			printf("%d\n", Current->Value);
		}
	}
}

void DeleteNode(int Value) {
	for (Node* Current = Head->Next; Current != Tail; Current = Current->Next) {
		if (Current->Value == Value) {
			Current->Prev->Next = Current->Next;    // ã������� �ճ���� ������带 ã������� �������� ����
			Current->Next->Prev = Current->Prev;    // ã������� ��������� �ճ�带 ã������� �ճ��� ����
			free(Current);                          // �ع�
			return;
		}
	}
}

void InsertBefore(int SearchValue, int Value) {
	for (Node* Current = Head->Next; Current != Tail; Current = Current->Next) {
		if (Current->Value == SearchValue) {
			Node* NewNode = MakeNode(Value);
			Current->Prev->Next = NewNode;
			NewNode->Prev = Current->Prev;
			NewNode->Next = Current;
			Current->Prev = NewNode;
		}
	}
}

void InsertAfter(int SearchValue, int Value)
{
	for (Node* Current = Head->Next; Current != Tail; Current = Current->Next) {
		if (Current->Value == SearchValue) {
			Node* NewNode = MakeNode(Value);

			Current->Next->Prev = NewNode;
			NewNode->Next = Current->Next;
			Current->Next = NewNode;
			NewNode->Prev = Current;
		}
	}
}
