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
			std::cerr << "Unexpected " << *expr << " at position " << expr - start << '\n';
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

		if (IsNumericSymbol(*expr) || (*expr == '-' && *(expr + 1) != ' ')) { // *expr -> positive or negative number
			numbers.Push(GetNumber(expr));
		}
		else { // *expr -> Operator
			op = GetOperation(expr);

			if (operations.Empty() || op == '(') {
				operations.Push(op);
				continue;
			}

			if (op == ')') { // Never push ) in the operator stack
				char tos;
				while ((tos = operations.Pop()) != '(') {
					if (operations.Empty())
						throw "Invalid expression -> Mismached brackets: too many ')'";

					numbers.Push(OM.Apply(tos, numbers.Pop(), numbers.Pop()));
				}
				continue;
			}

			stackTopPrecedence = (operations.Peak() == '(' ? -1 : OM.GetPrecedence(operations.Peak())); // Give ( lowest possible precedence (-1)
			opPrecedence = OM.GetPrecedence(op);

			if (stackTopPrecedence < opPrecedence) {
				operations.Push(op);
			}
			else if (stackTopPrecedence > opPrecedence) {
				numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
				--expr; // In case there is more than one preciding operation in the operations stack
			}
			else { // The two operations are of the same precedence
				if (OM.GetAssociativity(op) == OM.GetAssociativity(operations.Peak())) {
					if (OM.GetAssociativity(op) == Associativity::RIGHT) {
						operations.Push(op);
					}
					else {
						numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
						--expr; // In case there is more than one preciding operation in the operations stack
					}
				}
				else { // Operations are of the same precedence and different associativity
					throw "Invalid expression -> Cannot solve mixed associativity operators!";
				}
			}
		} // --operator

	} // --while

	while (!operations.Empty()) {
		if (operations.Peak() == '(') 
			throw "Invalid expression -> Mismached brackets: too many '('";
		numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
	}

	double result = numbers.Pop();
	if (!numbers.Empty())
		throw "Invalid expression -> Some numbers left";

	return result;
}

int main(int argc, char* argv[]) {

	//argv[2] = "E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\simpleTest.txt1";
	//argv[1] = "( ( 3 + 7 ) * 8 + 20";

	if (argc < 3) {
		cout << "Usage: ";
		cout << "InfixEvaluation \"<expression>\" <operators file>";
		return 1;
	}

	const char* operationsFile = argv[2];
	char* expr = argv[1];

	ifstream file(operationsFile);

	try {

		OperatorManager OM(file); // throws only (const char*)
		cout << Solve(expr, OM);

	}
	catch (const char* ex) {
		cout << ex;
	}

	file.close();

	return 0;
}
