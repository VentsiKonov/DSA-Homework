#pragma once
#include "Sorter.h"

template<typename T>
class InsertionSort : Sorter<T> {
public:

	virtual void sort(T * data, size_t count);

	virtual unsigned long long getSortTime() const;
};

template <class T>
unsigned long long InsertionSort<T>::getSortTime() const {
	return 0;
}

template <class T>
void InsertionSort<T>::sort(T* data, size_t count) {
	T inHand;
	size_t index;
	for (size_t i = 1; i < count - 1; i++) {
		inHand = data[i];
		index = i;
		while (index > 0 && inHand < data[index - 1]) {
			data[index] = data[index-1];
			--index;
		}
		data[index] = inHand;
	}
}
