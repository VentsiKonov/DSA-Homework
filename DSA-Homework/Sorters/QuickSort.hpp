#pragma once
#include "Sorter.h"
#include <ctime>
template <class T>
class QuickSort : public Sorter <T> {
public:
	virtual unsigned long long getSortTime() const;

	virtual void sort(T * data, size_t count);

private:
	size_t getPivotIndex(T* data, size_t count);
	void swap(T* data, size_t leftIndex, size_t rightIndex);
	size_t partition(T* data, size_t count, size_t pivotIndex);
	void quicksort(T* data, size_t count);

	clock_t time = 0;
	bool timeInit = false;
};

template <class T>
unsigned long long QuickSort<T>::getSortTime() const {
	return time;
}

template <class T>
void QuickSort<T>::swap(T* data, size_t leftIndex, size_t rightIndex) {
	T temp = data[leftIndex];
	data[leftIndex] = data[rightIndex];
	data[rightIndex] = temp;
}

template <class T>
size_t QuickSort<T>::getPivotIndex(T* data, size_t count) {
	if (count < 2)
		return 0;

	if (count < 3)
		return 1;

	if (data[0] > data[count - 1])
		swap(data, 0, count - 1);

	if (data[0] > data[count / 2])
		swap(data, 0, count / 2);

	if (data[count / 2] > data[count - 1])
		swap(data, count / 2, count - 1);

	swap(data, count / 2, count - 2);

	return count - 2;
}

template <class T>
size_t QuickSort<T>::partition(T* data, size_t count, size_t pivotIndex) {

	size_t lhs = 0; // 1;
	size_t rhs = count - 2; // 3;
	while (lhs < rhs) {
		while (lhs < pivotIndex && data[++lhs] < data[pivotIndex]) {
			//++lhs;
		}

		while (rhs > lhs && data[--rhs] > data[pivotIndex]) {
			//--rhs;
		}

		if (lhs < rhs)
			swap(data, lhs, rhs);
	}

	swap(data, lhs, pivotIndex);

	return lhs;

}

template <class T>
 void QuickSort<T>::quicksort(T* data, size_t count) {
	if (!timeInit) { 
		time = clock();
		timeInit = true;
	}

	if (count < 2)
		return;

	if (count < 3) {
		if (data[0] > data[1])
			swap(data, 0, 1);
		return;
	}

	size_t pivotIndex = getPivotIndex(data, count);

#ifdef _DEBUG1
	std::cout << "\tBefore partitioning:\n";
	for (size_t i = 0; i < count; i++) {
		std::cout << (i == pivotIndex ? "[" : "") << data[i] << (i == pivotIndex ? "]" : "") << " ";
	}
	std::cout << std::endl;
#endif

	size_t separationIndex = partition(data, count, pivotIndex);
#ifdef _DEBUG1
	std::cout << "\tAfter partitioning:\n";
		for (size_t i = 0; i < count; i++) {
			std::cout << data[i] << " ";
		}
	std::cout << std::endl;
#endif

	quicksort(data, separationIndex);
	quicksort(data + separationIndex + 1, count - separationIndex - 1);

#ifdef _DEBUG1
	std::cout << "\tAfter sort:\n";
	for (size_t i = 0; i < count; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
#endif
}

 template <class T>
 void QuickSort<T>::sort(T* data, size_t count) {
	 time = clock();

	 quicksort(data, count);

	 time = clock() - time;
 }