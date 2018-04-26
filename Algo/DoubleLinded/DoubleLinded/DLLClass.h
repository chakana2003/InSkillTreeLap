#pragma once

#include <stdio.h>
#include <stdlib.h>

// 탬플릿 활용 클래스

template<typename T>
class DLLNode                    // 노드 클래스
{
public:
	T Value;
	DLLNode* Prev;
	DLLNode* Next;
};

template<typename T>
class DLList {                  // 리스트 클래스
private:
	DLLNode<T>* Head;
	DLLNode<T>* Tail;
public:
	DLList();

	// 노드 추가하고 반환
	DLLNode<T>* MakeNode(T Value);

	// 꼬리에 노드를 추가하는 함수
	void AddNode(T Value);

	//앞에서부터 출력
	void PrintNodeFromHead();

	// 뒤에서부터 출력
	void PrintNodeFromTail();

	// Value 값 찾아서 삭제
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
void DLList<T>::AddNode(T Value) {       // 꼬리에 노드를 추가하는 함수
	if (Head == NULL) {         // 맨 처음 만들때
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
	{                          // 그 다음부터 만들때
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
			Current->Prev->Next = Current->Next;    // 찾은노드의 앞노드의 다음노드를 찾은노드의 다음노드로 설정
			Current->Next->Prev = Current->Prev;    // 찾은노드의 다음노드의 앞노드를 찾은노드의 앞노드로 설정
			free(Current);                          // 해방
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
