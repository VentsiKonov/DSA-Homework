#include "InsertionSort.hpp"
#include <iostream>

int main() {
	
	InsertionSort<int> sorter;
	int* data;
	data = new int[10];
	for (size_t i = 0; i < 10; i++) {
		data[i] = rand() % 15;
	}

	for (size_t i = 0; i < 10; i++) {
		std::cout << data[i] << " ";
	}

	std::cout << "\n";

	sorter.sort(data, 10);

	for (size_t i = 0; i < 10; i++) {
		std::cout << data[i] << " ";
	}
	return 0;
}