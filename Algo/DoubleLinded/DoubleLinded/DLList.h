#pragma once

typedef struct tagNode {
	int Value;
	tagNode* Prev;
	tagNode* Next;
}Node;

// ��� �߰��ϰ� ��ȯ
Node* MakeNode(int Value);

// ������ ��带 �߰��ϴ� �Լ�
void AddNode(int Value);

//�տ������� ���
void PrintNodeFromHead();

// �ڿ������� ���
void PrintNodeFromTail();

// Value �� ã�Ƽ� ����
void DeleteNode(int Value);

void InsertBefore(int SearchValue, int Value);

void InsertAfter(int SearchValue, int Value);

