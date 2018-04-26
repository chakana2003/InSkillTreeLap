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

	long Count; // 안에 들어있는 노드의 갯수

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
	if (Head->Next == Tail) { // 맨 처음만들 시
		DLLNode<T>* NewNode = new DLLNode<T>;
		NewNode->Prev = Head;
		NewNode->Next = Tail;
		NewNode->Value = Value;
		Head->Next = NewNode;
		Tail->Prev = NewNode;
	}
	else { // 일반적인 경우
		DLLNode<T>* NewNode = new DLLNode<T>;
		NewNode->Value = Value;
		// 생성된 노드의 전 노드가 Tail의 전 노드를 가르키게
		NewNode->Prev = Tail->Prev;
		// Tail 의 전 노드의 다음 노드가 생성된 노드를 가르키게
		Tail->Prev->Next = NewNode;
		// Tail 의 전 노드가 생성된 노드를 가르키게
		Tail->Prev = NewNode;
		// 생성된 노드의 다음 노드가 Tail 을 가르킴
		NewNode->Next = Tail;
	}
	++Count;
}

template<typename T>
inline void DLList<T>::Push_Front(T Value)
{
	// 맨 처음일 경우
	if (Head->Next == Tail) {
		Push_Back(Value);
	}
	else { // 일반적인 경우
		// 노드생성
		DLLNode<T>* NewNode = new DLLNode<T>;
		// 값 할당
		NewNode->Value = Value;
		// 생성된 노드의 다음노드가 Head의 다음노드를 가르키게
		NewNode->Next = Head->Next;
		// Head의 다음노드의 전노드가 생성된 노드를 가르키게
		Head->Next->Prev = NewNode;
		// Head의 다음노드가 생성된 노드를 가르키게
		Head->Next = NewNode;
		// 생성된 노드의 Prev 가 Head를 가르키게
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
