#pragma once

typedef struct tagNode {
	int Value;
	tagNode* Prev;
	tagNode* Next;
}Node;

// 노드 추가하고 반환
Node* MakeNode(int Value);

// 꼬리에 노드를 추가하는 함수
void AddNode(int Value);

//앞에서부터 출력
void PrintNodeFromHead();

// 뒤에서부터 출력
void PrintNodeFromTail();

// Value 값 찾아서 삭제
void DeleteNode(int Value);

void InsertBefore(int SearchValue, int Value);

void InsertAfter(int SearchValue, int Value);

