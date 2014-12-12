#include "Sorter.h"

template <class T>
class HeapSort : Sorter<T> {
public:
	virtual void sort(T* data, size_t count);
	virtual unsigned long long getSortTime() const;

private:
	void heapify(T* data, size_t count);
	void siftDown(T* data, size_t index);
	void siftUp(T* data, size_t index);
	void swap(T* data, size_t leftIndex, size_t rightIndex);

	size_t heapSize = 0;

	time_t time = 0;
};

template <class T>
void HeapSort<T>::swap(T* data, size_t leftIndex, size_t rightIndex) {
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

	if (heapSize < leftChildIndex) // No children
		return;

	if (heapSize < rightChildIndex) { // Exactly one child
		if (data[index] < data[leftChildIndex]) {
			swap(data, index, leftChildIndex);
		}
	}
	else {
		size_t biggerChildIndex;
		if (data[leftChildIndex] > data[rightChildIndex])
			biggerChildIndex = leftChildIndex;
		else
			biggerChildIndex = rightChildIndex;


		if (data[biggerChildIndex] > data[index]) {
			swap(data, index, biggerChildIndex);
			siftDown(data, biggerChildIndex);
		}
	}

}

template <class T>
void HeapSort<T>::heapify(T* data, size_t count) {
	while (count--) {
		siftUp(data, heapSize++);
	}
}

template <class T>
void HeapSort<T>::sort(T* data, size_t count) {
	time = clock();

	heapify(data, count);

	while (count--) {
		data[count] = data[0];
		data[0] = data[--heapSize];
		siftDown(data, 0);
	}

	time = clock() - time;
}