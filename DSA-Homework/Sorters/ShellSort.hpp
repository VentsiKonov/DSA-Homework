#include "Sorter.h"

template <class T>
class ShellSort : Sorter < T > {
public:
	virtual void sort(T* data, size_t count);
	virtual unsigned long long getSortTime() const;
private:
	void swap(T* data, size_t lhs, size_t rhs);

	time_t time = 0;
};

template <class T>
void ShellSort<T>::swap(T* data, size_t lhs, size_t rhs) {
	T temp = data[lhs];
	data[lhs] = data[rhs];
	data[rhs] = temp;
}

template <class T>
unsigned long long ShellSort<T>::getSortTime() const {
	return time;
}

template <class T>
void ShellSort<T>::sort(T* data, size_t count) {
	time = clock();

	for (size_t step = count/2; step >= 1; step /= 2) {
		for (size_t i = 0; i < count - step; i++) {
			if (data[i] > data[step + i]) {
				swap(data, i, step + i);
				size_t j = i;
				while (j >= 0) {
					if (j < step || j == 0)
						break;
					if (data[j] < data[j - step]) {
						swap(data, j, j - step);
					}
					else {
						break;
					}
					j -= step;
				}
#ifdef _DEBUG1
				for (size_t i = 0; i < count; i++) {
					std::cout << data[i] << " ";
				}
				std::cout << std::endl;
#endif
			}
		}
	}

	time = clock() - time;
}