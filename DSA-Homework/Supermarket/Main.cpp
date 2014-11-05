#include <iostream>
#include "List.h"
using namespace std;
int main() {
	{
		List<int> a;
		
		for (size_t i = 0; i < 20; i++) {
			a.PushBack(i);
		}

		List<int> b = a;

		a.PushAt(3, 30);
		a.PopFront();
		a.PopBack();
		a.PopAt(12);
		size_t size = a.Size();

		for (size_t i = 0; i < size; i++) {
			cout << a.PeakAt(i) << " " ;
		}
		cout << endl;

		size = b.Size();
		for (size_t i = 0; i < size; i++) {
			cout << b.PeakAt(i);
		}


	}
	_CrtDumpMemoryLeaks();
	return 0;
}