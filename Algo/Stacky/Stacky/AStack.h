#pragma once

template<typename T>
class AStack
{
protected:
	T * Data;     // ������ �迭
	int Capacity;  // �迭�� �ִ� ����
	int Size;      // �迭�� ���� ����
	int Top;       // �迭 �������� Index

public:
	void Init(int _Size);
	T Pop();
	void Push(T Value);
	int Length();
	int Peek();
};

template<typename T>
void AStack<T>::Init(int _Size)
{
	Data = new T[_Size];
	Capacity = _Size;
	Size = 0;
	Top = -1;
}

template<typename T>
T AStack<T>::Pop()
{
	T Value = 0;
	if (Size > 0) {
		Value = Data[Top];
		Top--;
		Size--;
	}
	return Value;
}

template<typename T>
void AStack<T>::Push(T Value)
{
	if (Capacity > Size) {
		Top++;
		Data[Top] = Value;
		Size++;
	}
	else {
		Capacity = Capacity * 2;
		T* NewData = new T[Capacity];
		memcpy(NewData, Data, (sizeof(T)*Size));
		delete[] Data;
		Data = NewData;

		Top++;
		Data[Top] = Value;
		Size++;
	}
}

template<typename T>
int AStack<T>::Length()
{
	return Size;
}

template<typename T>
int AStack<T>::Peek()
{
	return Top;
}
