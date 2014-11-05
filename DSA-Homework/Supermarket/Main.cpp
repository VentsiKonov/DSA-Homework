#include <iostream>
#include "List.h"
#include "Queue.h"

using namespace std;
int main() {
	{
		Queue<int> a;
		for (size_t i = 0; i < 10; i++) {
			a.Push(i);
		}

		Queue<int> b(a);
		a.Clear();
		a = b;
		size_t size = b.Size();
		for (size_t i = 0; i < size; i++) {
			cout << b.Pop();
		}
		a = a;
		size = a.Size();
		cout << "new a:" << endl;
		for (size_t i = 0; i < size; i++) {
			cout << a.Pop();
		}

	}
	_CrtDumpMemoryLeaks();
	return 0;
}