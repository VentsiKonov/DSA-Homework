#include "SortTester.h"
#include <iostream>
#include "MergeSort.hpp"
#include "InsertionSort.hpp"
#include "HeapSort.hpp"
#include "ShellSort.hpp"
#include "QuickSort.hpp"
#include <iomanip>

template <class T>
class SortTesterClass : SortTester < T > {
public:
	SortTesterClass(Sorter<T> ** sorters, int count);
	virtual void getSummary(std::ostream & out);
	~SortTesterClass();
private:
	T* data = NULL;
	size_t dataSize = 0;
	Sorter<T> ** sorters;
	size_t sortersCount = 0;
	size_t** times;
	size_t testsCount = 0;
};

template <class T>
SortTesterClass<T>::~SortTesterClass() {
	for (size_t i = 0; i < sortersCount; i++) {
		delete[] times[i];
	}
}

template <class T>
SortTesterClass<T>::SortTesterClass(Sorter<T> ** sorters, int count) 
	: SortTester<T>(sorters, count) {
	this->sorters = sorters;
	this->sortersCount = count;
	srand(time(NULL));
	dataSize = 100000;//rand() * 100;
	times = new size_t*[count];
	testsCount = 4;
	for (size_t i = 0; i < count; i++) {
		times[i] = new size_t[testsCount];
	}
	
	// Sorted data
	for (size_t i = 0; i < count; i++) {
		try {
			delete[] data;
			data = new T[dataSize];
			for (size_t j = 0; j < dataSize; ++j) {
				data[j] = j;
			}
			
		}
		catch (std::bad_alloc ex) {
			std::cerr << "Unable to create test data! Exiting!";
			return;
		}

		if (sorters[i]) { 
			sorters[i]->sort(data, dataSize);
			times[i][0] = sorters[i]->getSortTime();
		}
	}

	// Half sorted, half reverse data
	for (size_t i = 0; i < count; i++) {
		try {
			delete[] data;
			data = new T[dataSize];
			bool reverse = false;
			int k = 0;
			for (size_t j = 0; j < dataSize; ++j) {
				data[j] = k;
				if (j == dataSize / 2) reverse = true;
				if (reverse) --k; else ++k;
			}

		}
		catch (std::bad_alloc ex) {
			std::cerr << "Unable to create test data! Exiting!";
			return;
		}

		if (sorters[i]) {
			sorters[i]->sort(data, dataSize);
			times[i][1] = sorters[i]->getSortTime();
		}
	}

	// Reverse data
	for (size_t i = 0; i < count; i++) {
		try {
			delete[] data;
			data = new T[dataSize];
			for (size_t j = 0; j < dataSize; ++j) {
				data[j] = dataSize - j;
			}

		}
		catch (std::bad_alloc ex) {
			std::cerr << "Unable to create test data! Exiting!";
			return;
		}

		if (sorters[i]) {
			sorters[i]->sort(data, dataSize);
			times[i][2] = sorters[i]->getSortTime();
		}
	}

	// Random data
	for (size_t i = 0; i < count; i++) {
		try {
			delete[] data;
			data = new T[dataSize];
			for (size_t j = 0; j < dataSize; ++j) {
				data[j] = rand();
			}

		}
		catch (std::bad_alloc ex) {
			std::cerr << "Unable to create test data! Exiting!";
			return;
		}

		if (sorters[i]) {
			sorters[i]->sort(data, dataSize);
			times[i][3] = sorters[i]->getSortTime();
		}
	}
}

template <class T>
void SortTesterClass<T>::getSummary(std::ostream& out) {
	out << "For each algorithm was supplied and array of data with size: " << dataSize << std::endl;
	out << "Size of one entry in the data is: " << sizeof(T) << std::endl; //<< " (" << typeid(T).name() << ")" << std::endl;
	out << "Total data size: " << sizeof(T) * dataSize << std::endl;
	for (size_t i = 0; i < sortersCount; i++) {
		out << "Sorter " << i << ":\n";
		out << "\t" << std::setw(33) << "Sorted data: " << std::setw(10) << times[i][0] << " ticks.\n";
		out << "\t" << std::setw(33) << "Half-sorted, half-reverse data: " << std::setw(10) << times[i][1] << " ticks.\n";
		out << "\t" << std::setw(33) << "Reverse data: " << std::setw(10) << times[i][2] << " ticks.\n";
		out << "\t" << std::setw(33) << "Random data: " << std::setw(10) << times[i][3] << " ticks.\n";
	}
}