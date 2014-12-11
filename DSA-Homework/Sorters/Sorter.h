#pragma once

template<typename T>
class Sorter {
public:
	virtual unsigned long long getSortTime() const = 0;

	virtual void sort(T * data, size_t count) = 0;

};