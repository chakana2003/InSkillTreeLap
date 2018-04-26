#pragma once

template<typename T>
class DLLNode {
public:
	T Value;
	DLLNode<T>* Prev;
	DLLNode<T>* Next;
};

template<typename T>
class DLList {
private:
	DLLNode<T>* Head;
	DLLNode<T>* Tail;

	long Count; // �ȿ� ����ִ� ����� ����

public:
	DLList();
	DLLNode<T>* DeleteNode(T SearchValue);
	void Push_Back(T Value);
	void Push_Front(T Value);
	DLLNode<T>* FindNode(T SearchValue);
	DLLNode<T>* IndexOf(int Index);
	DLLNode<T>* GetEnd();
	long GetCount();
};

template<typename T>
inline DLList<T>::DLList() {
	Head = new DLLNode<T>;
	Tail = new DLLNode<T>;
	Head->Next = Tail;
	Tail->Prev = Head;
	Count = 0;
}

template<typename T>
inline DLLNode<T> * DLList<T>::DeleteNode(T SearchValue)
{
	DLLNode<T>* Target = FindNode(SearchValue);
	if (Target) {
		DLLNode<T>* ReturnNode = Target->Prev;
		Target->Prev->Next = Target->Next;
		Target->Next->Prev = Target->Prev;
		delete(Target);
		return ReturnNode;
	}
	return NULL;
}

template<typename T>
inline void DLList<T>::Push_Back(T Value)
{
	if (Head->Next == Tail) { // �� ó������ ��
		DLLNode<T>* NewNode = new DLLNode<T>;
		NewNode->Prev = Head;
		NewNode->Next = Tail;
		NewNode->Value = Value;
		Head->Next = NewNode;
		Tail->Prev = NewNode;
	}
	else { // �Ϲ����� ���
		DLLNode<T>* NewNode = new DLLNode<T>;
		NewNode->Value = Value;
		// ������ ����� �� ��尡 Tail�� �� ��带 ����Ű��
		NewNode->Prev = Tail->Prev;
		// Tail �� �� ����� ���� ��尡 ������ ��带 ����Ű��
		Tail->Prev->Next = NewNode;
		// Tail �� �� ��尡 ������ ��带 ����Ű��
		Tail->Prev = NewNode;
		// ������ ����� ���� ��尡 Tail �� ����Ŵ
		NewNode->Next = Tail;
	}
	++Count;
}

template<typename T>
inline void DLList<T>::Push_Front(T Value)
{
	// �� ó���� ���
	if (Head->Next == Tail) {
		Push_Back(Value);
	}
	else { // �Ϲ����� ���
		// ������
		DLLNode<T>* NewNode = new DLLNode<T>;
		// �� �Ҵ�
		NewNode->Value = Value;
		// ������ ����� ������尡 Head�� ������带 ����Ű��
		NewNode->Next = Head->Next;
		// Head�� ��������� ����尡 ������ ��带 ����Ű��
		Head->Next->Prev = NewNode;
		// Head�� ������尡 ������ ��带 ����Ű��
		Head->Next = NewNode;
		// ������ ����� Prev �� Head�� ����Ű��
		NewNode->Prev = Head;
	}
}

template<typename T>
inline DLLNode<T> * DLList<T>::FindNode(T SearchValue)
{
	/*DLLNode<T>* Target;
	for (Target = Head; Target != Tail; Target = Target->Next) {
		if (Target->Value == SearchValue) {
			return Target;
		}
	}*/

	for (DLLNode<T>* Current = Head; Current != Tail; Current = Current->Next) {
		if (Current->Value == SearchValue) {
			return Current;
		}
	}
	return NULL;
}

template<typename T>
inline DLLNode<T>* DLList<T>::IndexOf(int Index)
{
	long ObjectCount = 0;
	for (DLLNode<T>* Current = Head; Current != Tail; Current = Current->Next) {
		if ((ObjectCount == Index) && (Index != 0) && (Index < Count)) {
			return Current;
		}
		ObjectCount++;
	}
	return NULL;
}

template<typename T>
inline long DLList<T>::GetCount()
{
	return Count;
}

template<typename T>
inline DLLNode<T>* DLList<T>::GetEnd()
{
	return Tail;
}
