#include "SortTesterClass.hpp"
#include "QuickSort.hpp"
#include "MergeSort.hpp"
#include "InsertionSort.hpp"
#include "HeapSort.hpp"
#include "ShellSort.hpp"
#include <iostream>

// Testing structure
struct MyStruct {
	int a[49];
	int index;
	bool operator<(MyStruct& rhs) const {
		return this->index < rhs.index;
	}
	bool operator>=(MyStruct& rhs) const {
		return !(*this < rhs);
	}
	bool operator>(MyStruct& rhs) const {
		return this->index > rhs.index;
	}
	bool operator<=(MyStruct& rhs) const {
		return !(*this > rhs);
	}
	bool operator==(MyStruct& rhs) const {
		return this->index == rhs.index;
	}
	bool operator!=(MyStruct& rhs) const {
		return !(*this == rhs);
	}
	MyStruct& operator=(int v) {
		index = v;
		return *this;
	}
};

int main() {

	std::cout << "Initializing data and runnig sort algorithms...\n\n";

	try {
		Sorter<double> ** sorters = new Sorter<double>*[5];
		sorters[0] = new QuickSort<double>();
		sorters[1] = new HeapSort<double>();
		sorters[2] = new MergeSort<double>();
		sorters[3] = new ShellSort<double>();
		sorters[4] = new InsertionSort<double>();

		SortTesterClass<double> intTester(sorters, 4);
		intTester.getSummary(std::cout);
		std::cout << std::endl;

		for (size_t i = 0; i < 5; i++) {
			delete sorters[i];
		}

	}
	catch (std::bad_alloc ex) {
		std::cerr << "Unable to initialize sorters!";
	}

	std::cout << "Initializing data and runnig sort algorithms...\n\n";
	
	try {
		Sorter<MyStruct> ** sorters = new Sorter<MyStruct>*[5];
		sorters[0] = new QuickSort<MyStruct>();
		sorters[1] = new HeapSort<MyStruct>();
		sorters[2] = new MergeSort<MyStruct>();
		sorters[3] = new ShellSort<MyStruct>();
		sorters[4] = new InsertionSort<MyStruct>();
	
		SortTesterClass<MyStruct> intTester(sorters, 4);
		intTester.getSummary(std::cout);
		std::cout << std::endl;
	
		for (size_t i = 0; i < 5; i++) {
			delete sorters[i];
		}
	
	}
	catch (std::bad_alloc ex) {
		std::cerr << "Unable to initialize sorters!";
	}	

	return 0;
}

