#pragma once

template<typename T>
class AStack
{
protected:
	T * Data;     // 데이터 배열
	int Capacity;  // 배열의 최대 길이
	int Size;      // 배열의 실제 길이
	int Top;       // 배열 마지막의 Index

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
