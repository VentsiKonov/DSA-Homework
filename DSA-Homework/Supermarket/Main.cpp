#include <iostream>
#include <vector>

#include "List.h"

using namespace std;
int main() {
	{
		List<int> a;
		for (size_t i = 0; i < 10; i++) {
			a.PushBack(i);
		}
		for (List<int>::Iterator i = a.Begin(); i != a.End(); ++i) {
			cout << *i;
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}