#include <iostream>
#include <fstream>

#include "Stack.h"
#include "OperatorManager.h"

using std::endl;
using std::ifstream;
using std::cout;
using std::ios;

int main(int argc, char* argv[]) {
		{
			argv[2] = "E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\TestOperators1.txt";
			const char* operationsFile = argv[2];
			//const char* expression = argv[1];

			ifstream file(operationsFile, ios::in); // Doesn't throw exception on failure

			try {
				OperatorManager OM(file); // throws only (const char*)
				file.close();

				OM.PrintOperators();

			}
			catch (const char* ex) {
				std::cerr << ex;
			}


		}
	_CrtDumpMemoryLeaks();
	return 0;
}