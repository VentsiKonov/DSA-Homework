#include <iostream>
#include "Stack.h"
#include <string.h>
#include <fstream>
#include "OperatorManager.h"

using namespace std;

int main() {
		{
			ifstream file("E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\TestOperators1.txt", ios::in);
			OperatorManager OM(file);
			file.close();
			OM.PrintOperators();
			for (size_t i = 40; i < 50; i++) {
				cout << i << " " << (char)i << endl;
			}

			// Decide on whether keeping to the assoc array idea or changing it when it's not too late!!
			// Ask about double and symbols for operations
		}
	_CrtDumpMemoryLeaks();
	return 0;
}