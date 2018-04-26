#pragma once

#include <list>

template<typename T>
class Queue {
public:
	void Enquere(T Value);
	void Dequeue(T& Value);
	int IsEmpty();
	int Length();
	void Peek(T& Value);

protected:
	std::list<T> Data;
};

template<typename T>
void Queue<T>::Enquere(T Value)
{
	Data.push_back(Value);
}

template<typename T>
void Queue<T>::Dequeue(T & Value)
{
	Value = Data.front();
	Data.pop_front();
}

template<typename T>
int Queue<T>::IsEmpty()
{
	return (Data.empty());
}

template<typename T>
int Queue<T>::Length()
{
	return Data.size();
}

template<typename T>
void Queue<T>::Peek(T & Value)
{
	Value = Data.front();
}
