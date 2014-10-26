#include <iostream>
#include "Stack.h"
#include "OperatorManager.h"

using std::ifstream;
using std::cout;

bool IsNumericSymbol(char s) {
	return (s >= '0' && s <= '9');
}

bool ValidBrackets(const char* expr) {
	int count = 0;
	const char* start = expr;
	while (*expr != '\0') {
		if (*expr == '(') ++count;
		else if (*expr == ')') --count;

		if (count < 0) {
			std::cerr << "Unexpected " << *expr << " at position " << expr-start << '\n';
			return 0;
		}
		++expr;
	}
	if (count != 0) {
		std::cerr << "Expcted " << count << " )" << '\n';
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
	
	//TrimStart(string);
	
	while ((IsNumericSymbol(*string) || (*string == ',' || *string == '.' || *string == '-')) && count < 10) { // Ugly -> TODO: Split to several bools
		if (*string == ',') 
			subs[count++] = '.';
		else 
			subs[count++] = *string;
	
		++string;
	}
	
	subs[count + 1] = '\0';

	return atof(subs);
}

char GetOperation(char* &string) {
	return *(string++);
}

double Solve(char* expr, const OperatorManager& OM) {

	Stack<char> operations;
	Stack<double> numbers;
	char op;
	int stackTopPrecedence;
	int opPrecedence;

	while (*expr != '\0') { // GetNumber() and GetOperation() move the pointer
		TrimStart(expr); // Essential

		if (IsNumericSymbol(*expr) || (*expr == '-' && *(expr + 1) != ' ')) { // positive or negative number
			numbers.Push(GetNumber(expr));
		}
		else { // Operator
			op = GetOperation(expr);

			if (operations.Empty() || op == '(') {
				operations.Push(op);
				continue;
			}

			if (op == ')') {
				char top;
				while ((top = operations.Pop()) != '(') {
					numbers.Push(OM.Apply(top, numbers.Pop(), numbers.Pop()));
				}
				continue;
			}

			char top = operations.Peak();
			stackTopPrecedence = (top == '(' ? -1 : OM.GetPrecedence(top)); // Give ( lowest possible precedence
			opPrecedence = OM.GetPrecedence(op);
			
			if (stackTopPrecedence < opPrecedence) {
				operations.Push(op);
			}
			else if (stackTopPrecedence > opPrecedence) {
				numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
				--expr; // In case there is more than one preciding operation in the operations stack
			}
			else { // The two operations are of the same precedence

			}
		} // --operator

	} // --while

	while (!operations.Empty()) {
		numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
	}

	double result = numbers.Pop();
	//if (!numbers.Empty())
	//	throw "More operations are expected!";

	return result;
}


int main(int argc, char* argv[]) {
		{
			argv[2] = "E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\simpleTest.txt";
			argv[1] = "3 * ( 3 + 2 * 2 ) + 5";
			
			const char* operationsFile = argv[2];
			char* expr = argv[1];
			
			ifstream file(operationsFile); // Doesn't throw exception on failure
			
			OperatorManager OM(file); // throws only (const char*)
			file.close();
			
			//OM.PrintOperators();
			
			cout << Solve(expr, OM);

		}
	_CrtDumpMemoryLeaks();
	return 0;
}