#include "InsertionSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "MergeSort.hpp"
#include "ShellSort.hpp"

#include <iostream>
 
bool isSorted(int* data[], size_t arrays, size_t count) {
	for (size_t i = 1; i < arrays; i++) {
		for (size_t j = 0; j < count; ++j) {
			if (data[i][j] != data[0][j]) {
				std::cout << data[0][j] << " != " << data[i][j] << std::endl;
				std::cout << "Not sorted: " << i << std::endl;
				return false;
			}
		}
	}
	//for (size_t i = 1; i < count; ++i) {
	//	if (data[i - 1] > data[i])
	//		return false;
	//}
	return true;
}

int main() {
	QuickSort<int> quick;
	InsertionSort<int> insertion;
	HeapSort<int> heap;
	MergeSort<int> merge;
	ShellSort<int> shell;

	int *data, *data2, *data3, *data4, *data5;

	size_t count = 1000000;

	data = new int[count];
	data2 = new int[count];
	data3 = new int[count];
	data4 = new int[count];
	data5 = new int[count];

	for (size_t i = 0; i < count; i++) {
		data[i] = data2[i] = data3[i] = data4[i] = data5[i] = rand() % 5000;
	}
#ifdef _DEBUG1
	for (size_t i = 0; i < count; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
#endif

	// head

	heap.sort(data, count);
	std::cout << heap.getSortTime() << " ticks heap." << std::endl;
	quick.sort(data2, count); 
	std::cout << quick.getSortTime() << " ticks quick." << std::endl;
	merge.sort(data4, count);
	std::cout << merge.getSortTime() << " ticks merge." << std::endl;
	shell.sort(data5, count);
	std::cout << shell.getSortTime() << " ticks shell." << std::endl;
	//insertion.sort(data3, count);
	//std::cout << insertion.getSortTime() << " ticks insertion." << std::endl;

	// foot
#ifdef _DEBUG1
	for (size_t i = 0; i < count; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;

#endif
	int* arrays[] = {data, data2, data4, data5};
	bool sorted = isSorted(arrays, 4, count);
	std::cout << "Sorted: " << sorted << std::endl;
	//std::cout << "Heap swaps: " << heap.getSwapsCount() << std::endl;
	//if (!sorted) {
		//for (size_t i = 0; i < count; i++) {
		//	std::cout << data[i] << " ";
		//}
	std::cout << std::endl;
	//}
	return 0;
}

