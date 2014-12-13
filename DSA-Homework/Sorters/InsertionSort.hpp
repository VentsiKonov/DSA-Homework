#pragma once
#include "Sorter.h"
#include <ctime>
template<typename T>
class InsertionSort : Sorter<T> {
public:

	virtual void sort(T * data, size_t count);

	virtual unsigned long long getSortTime() const;

private:
	clock_t time;
};

template <class T>
unsigned long long InsertionSort<T>::getSortTime() const {
	return time;
}

template <class T>
void InsertionSort<T>::sort(T* data, size_t count) {
	time = clock();
	T inHand;
	size_t index;
	for (size_t i = 1; i < count; i++) {
#ifdef _DEBUG1
		for (size_t j = 0; j < count; j++) {
			std::cout << data[j] << " ";
		}
		std::cout << std::endl;
#endif
		inHand = data[i];
		index = i;
		while (index > 0 && inHand < data[index - 1]) {
			data[index] = data[index-1];
			--index;
		}
		data[index] = inHand;
	}
	time = clock() - time;
}
