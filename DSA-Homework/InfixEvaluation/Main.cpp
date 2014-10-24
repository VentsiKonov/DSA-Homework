#include <iostream>
#include "Stack.h"
#include <string.h>
#include <fstream>
#include "OperatorManager.h"

using namespace std;

int main(int argc, char* argv[]) {
		{
			argv[2] = "E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\TestOperators1.txt";


			ifstream file(argv[2], ios::in);
			
			try {
				OperatorManager OM(file); // throws only (const char*)
				file.close();



			}
			catch (const char* ex) {
				file.close();
				std::cerr << ex;
			}

		}
	_CrtDumpMemoryLeaks();
	return 0;
}