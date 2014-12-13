#include "Sorter.h"
#include <iostream>
template<typename T>
class SortTester {
public:
	SortTester(Sorter<T> ** sorters, int count) {}
	virtual void getSummary(std::ostream & out) = 0;
};