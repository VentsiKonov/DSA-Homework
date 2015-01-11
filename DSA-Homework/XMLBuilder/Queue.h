#pragma once
#include "List.h"

template <class T>
class Queue : protected List<T> {
public:
	Queue() : List<T>() {}
	Queue(const Queue<T>& q) : List<T>(q) {}
	Queue<T>& operator=(const Queue<T>& q);
	
	void Push(const T& data);
	T Pop();
	T& Peek() const;
	size_t Size() const;
	void Clear();
	bool IsEmpty() const;
};

template <class T>
void Queue<T>::Push(const T& data) {
	List<T>::PushBack(data);
}

template <class T>
T Queue<T>::Pop() {
	return List<T>::PopFront();
}

template <class T>
bool Queue<T>::IsEmpty() const {
	return List<T>::IsEmpty();
}

template <class T>
size_t Queue<T>::Size() const {
	return List<T>::Size();
}

template <class T>
T& Queue<T>::Peek() const {
	return List<T>::Front();
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q) {
	List<T>::operator=(q);
	return *this;
}

template <class T>
void Queue<T>::Clear() {
	List<T>::Clear();
}
