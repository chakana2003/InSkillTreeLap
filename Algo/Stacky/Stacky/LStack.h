#pragma once

#include "LinkL.h"

template<typename T>
class LStack
{
protected:
	DLList<T> Data;

public:
	T Pop();
	void Push(T Value);
	T Peek();
	long Length() { return Data.GetCount(); }
};

template<typename T>
T LStack<T>::Pop()
{
	T Value = 0;
	if (Data.GetCount() > 0) {
		Value = Data.GetEnd()->Prev->Value;
		Data.DeleteNode(Value);
	}
	return Value;
}

template<typename T>
void LStack<T>::Push(T Value)
{
	Data.Push_Back(Value);
}

template<typename T>
T LStack<T>::Peek()
{
	T Value = 0;
	if (Data.GetCount() > 0) {
		Value = Data.GetEnd()->Prev->Value;
	}

	return Value;
}
