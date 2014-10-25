#include <iostream>
#include <fstream>

#include "Stack.h"
#include "OperatorManager.h"

using std::endl;
using std::ifstream;
using std::cout;
using std::ios;

bool ValidBrackets(const char* expr) {
	int count = 0;
	const char* start = expr;
	while (*expr != '\0') {
		if (*expr == '(') ++count;
		else if (*expr == ')') --count;

		if (count < 0) {
			std::cerr << "Unexpected " << *expr << " at position " << expr-start<< endl;
			return 0;
		}
		++expr;
	}
	if (count != 0) {
		std::cerr << "Expcted " << count << " )" << endl;
		return false;
	}

	return true;
}

void TrimStart(char* &string) {
	while (*string == ' ')
		++string;
}

double GetNumber(char* &string) { 
	size_t count = 0;
	char subs[12]; // 12 -> Maximal possible length of unsigned int and double
	
	TrimStart(string);
	
	while (((*string >= '0' && *string <= '9') || (*string == ',' || *string == '.' || *string == '-')) && count < 10) {
		if (*string == ',') 
			subs[count++] = '.';
		else 
			subs[count++] = *string;
	
		++string;
	}
	
	subs[count + 1] = '\0';

	return atof(subs);
}

char GetChar(char* &string) {
	TrimStart(string);
	return *(string++);
}

double Solve(const char* expr, const OperatorManager& OM) {
	
	Stack<char> operations;
	Stack<double> numbers;
	return 0;
}


int main(int argc, char* argv[]) {
		{
			argv[2] = "E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\TestOperators1.txt";
			argv[1] = "31.41428 a ( 5 b 32 f 10 e -230) c 324 d 17";
			
			const char* operationsFile = argv[2];
			char* expr = argv[1];
			
			//ifstream file(operationsFile, ios::in); // Doesn't throw exception on failure
			//
			//OperatorManager OM(file); // throws only (const char*)
			//file.close();
			//
			//OM.PrintOperators();
			//
			//Solve(expr, OM);
			
			while (*expr != '\0') {
				TrimStart(expr);
				if ((*expr >= '0' && *expr <= '9') || (*expr == '-' && *(expr+1) != ' '))
					cout << GetNumber(expr);
				else
					cout << GetChar(expr);

				cout << endl;

			}

		}
	_CrtDumpMemoryLeaks();
	return 0;
}