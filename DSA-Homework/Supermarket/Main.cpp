#include <iostream>
#include "List.h"
using namespace std;
int main() {
	{
		List<int> a;
		a.PushFront(5);
		a.PushBack(10);
		std::cout << a.PeakFront() << " " << a.PeakBack();
		List<int> b(a);
		a.Clear();
		std::cout << b.PeakAt(1) << " " << b.PopBack();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}