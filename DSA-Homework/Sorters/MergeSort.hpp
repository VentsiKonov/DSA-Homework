#include "Sorter.h"

template <class T>
class MergeSort : Sorter < T > {
public:
	virtual void sort(T* data, size_t count);
	virtual unsigned long long getSortTime() const;

private:
	void merge(T* input, T* output, size_t leftStart, size_t rightStart, size_t rightEnd);
	size_t min(size_t lhs, size_t rhs) {
		return lhs < rhs ? lhs : rhs;
	}

	T* workArray;
	time_t time = 0;
};

template <class T>
unsigned long long MergeSort<T>::getSortTime() const {
	return time;
}

template <class T>
void MergeSort<T>::merge(T* input, T* output, size_t leftStart, size_t rightStart, size_t rightEnd) {
	
	size_t left = leftStart;
	size_t right = rightStart;
	size_t writer = leftStart;

	while (writer < rightEnd) {
		if (right >= rightEnd || (left < rightStart && input[left] < input[right])) {
			output[writer++] = input[left++];
		}
		else {
			output[writer++] = input[right++];
		}
	}

}

template <class T>
void MergeSort<T>::sort(T* data, size_t count) {
	time = clock();
	try {
		workArray = new T[count];
	}
	catch (std::bad_alloc ex) {
		std::cerr << "Merge sort failed! No enough space!";
		return;
	}

	size_t runNumber = 0;
	T *input, *output;
	for (size_t size = 1; size < count; size *= 2) {
		for (size_t i = 0; i < count; i += 2*size) {
			if (runNumber % 2 == 0) {
				input = data;
				output = workArray;
			}
			else {
				input = workArray;
				output = data;
			}
			merge(input, output, i, min(i + size, count), min(i + 2 * size, count));
		}
		++runNumber;
	}

	if (runNumber % 2 != 0) {
		for (size_t i = 0; i < count; i++) {
			data[i] = workArray[i];
		}
	}

	delete[] workArray;

	time = clock() - time;
}