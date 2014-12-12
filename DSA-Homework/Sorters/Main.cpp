#include "InsertionSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"

#include <iostream>

bool isSorted(int* data, size_t count) {
	for (size_t i = 1; i < count; ++i) {
		if (data[i - 1] > data[i])
			return false;
	}
	return true;
}

int main() {

	QuickSort<int> quick;
	InsertionSort<int> insertion;
	HeapSort<int> heap;

	int* data;
	size_t count = 10000000;
	data = new int[count];
	for (size_t i = 0; i < count; i++) {
		data[i] = rand() % 5000;
	}
#ifdef _DEBUG
	for (size_t i = 0; i < count; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
#endif
	std::cout << "\n";

	// head

	heap.sort(data, count);

	// foot
	bool sorted = isSorted(data, count);
	std::cout << "Sorted: " << sorted << std::endl;
	if (!sorted) {
		for (size_t i = 0; i < count; i++) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << heap.getSortTime() << " ticks." << std::endl;
	return 0;
}

