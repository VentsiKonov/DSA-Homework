#include "Sorter.h"

template <class T>
class HeapSort : Sorter<T> {
public:
	virtual void sort(T* data, size_t count);
	virtual unsigned long long getSortTime() const;

	size_t getSwapsCount() const;
private:
	void heapify(T* data, size_t count);
	void siftDown(T* data, size_t index);
	void siftUp(T* data, size_t index);
	void swap(T* data, size_t leftIndex, size_t rightIndex);

	size_t heapSize = 0;
	time_t time = 0;
	size_t swaps = 0;
};

template <class T>
size_t HeapSort<T>::getSwapsCount() const {
	return swaps;
}

template <class T>
void HeapSort<T>::swap(T* data, size_t leftIndex, size_t rightIndex) {
	++swaps;
	T temp = data[leftIndex];
	data[leftIndex] = data[rightIndex];
	data[rightIndex] = temp;
}

template <class T>
unsigned long long HeapSort<T>::getSortTime() const {
	return time;
}

template <class T>
void HeapSort<T>::siftUp(T* data, size_t index) {
	if (index == 0) return;

	size_t parentIndex = (index - 1) / 2;

	if (data[parentIndex] < data[index]) {
		swap(data, parentIndex, index);
		siftUp(data, parentIndex);
	}
}

template <class T>
void HeapSort<T>::siftDown(T* data, size_t index) {
	size_t leftChildIndex = 2 * index + 1;
	size_t rightChildIndex = 2 * index + 2;
	size_t biggerChildIndex = leftChildIndex;

	while (biggerChildIndex < heapSize) {
		leftChildIndex = 2 * index + 1;
		rightChildIndex = 2 * index + 2;
		biggerChildIndex = leftChildIndex;

		if (biggerChildIndex >= heapSize)
			break;

		if (biggerChildIndex + 1 < heapSize && data[biggerChildIndex] < data[biggerChildIndex + 1])
			++biggerChildIndex;

		if (data[biggerChildIndex] < data[index])
			break;

		swap(data, biggerChildIndex, index);
		index = biggerChildIndex;
	}

	// Recursion hurts performance?

	//if (heapSize <= leftChildIndex) // No children
	//	return;
	//
	//if (heapSize <= rightChildIndex) { // Exactly one child
	//	if (data[index] < data[leftChildIndex]) {
	//		swap(data, index, leftChildIndex);
	//	}
	//}
	//else {
		//if (data[leftChildIndex] > data[rightChildIndex])
		//	biggerChildIndex = leftChildIndex;
		//else
		//	biggerChildIndex = rightChildIndex;
		//
		//if (data[biggerChildIndex] > data[index]) {
		//	swap(data, index, biggerChildIndex);
		//	siftDown(data, biggerChildIndex);
		//}
	//}


}

template <class T>
void HeapSort<T>::heapify(T* data, size_t count) {
	//while (--count >= 0) {
	//	siftUp(data, heapSize++);
	//	if (count == 0) break;
	//}
	heapSize = count;
	for (size_t i = count/2 - 1; i >= 0; --i) {
		siftDown(data, i);
		if (i == 0) break;
	}
}

template <class T>
void HeapSort<T>::sort(T* data, size_t count) {
	time = clock();

	heapify(data, count);
#ifdef _DEBUG1
	for (size_t i = 0; i < count; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
#endif
	while (heapSize-- > 0) {
		swap(data, 0, heapSize);
		siftDown(data, 0);
	}

	time = clock() - time;
}