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

void AddNode(int Value) {       // 꼬리에 노드를 추가하는 함수
	if (Head == NULL) {         // 맨 처음 만들때
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
	{                          // 그 다음부터 만들때
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
			Current->Prev->Next = Current->Next;    // 찾은노드의 앞노드의 다음노드를 찾은노드의 다음노드로 설정
			Current->Next->Prev = Current->Prev;    // 찾은노드의 다음노드의 앞노드를 찾은노드의 앞노드로 설정
			free(Current);                          // 해방
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
