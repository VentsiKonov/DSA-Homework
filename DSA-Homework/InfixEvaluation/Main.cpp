#include <iostream>
#include "Stack.h"
#include "OperatorManager.h"

using std::ifstream;
using std::cout;

bool IsNumericSymbol(char s) {
	return (s >= '0' && s <= '9');
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

	char op, stackTop;
	int stackTopPrecedence, opPrecedence;
	Associativity opAssoc, stackTopAssoc;

	while (*expr != '\0') { // GetNumber() and GetOperation() move the pointer
		TrimStart(expr); // Essential

		if (IsNumericSymbol(*expr) || (*expr == '-' && *(expr + 1) != ' ')) { // *expr is positive or negative number
			numbers.Push(GetNumber(expr));
		}
		else { // *expr is Operator
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

					if (numbers.Size() < 2)
						throw "Invalid expression -> Not enough numbers";

					numbers.Push(OM.Apply(tos, numbers.Pop(), numbers.Pop()));
				}
				continue;
			}

			stackTop = operations.Peak();
			stackTopPrecedence = (stackTop == '(' ? -1 : OM.GetPrecedence(stackTop)); // Give '(' lowest possible precedence (-1)
			stackTopAssoc = (stackTop == '(' ? Associativity::RIGHT : OM.GetAssociativity(stackTop)); // Give '(' right associativity

			opPrecedence = OM.GetPrecedence(op);
			opAssoc = OM.GetAssociativity(op);
			bool equalAssoc = (opAssoc == stackTopAssoc);

			if (stackTopPrecedence < opPrecedence || (stackTopPrecedence == opPrecedence && equalAssoc && opAssoc == Associativity::RIGHT)) {
				// Either different precedence or equal precedence and equal RIGHT associativity
				operations.Push(op);
			}
			else if (stackTopPrecedence > opPrecedence || (equalAssoc && opAssoc == Associativity::LEFT)) {
				// Either different precedence or equal precedence and equal LEFT associativity
				numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
				--expr; // In case there is more than one preciding operation in the operations stack
			}
			else { // The two operations are of the same precedence and different associativity
				throw "Invalid expression -> Cannot solve mixed associativity operators!";
			}


		} // --operator

	} // --while

	while (!operations.Empty()) {
		if (operations.Peak() == '(')
			throw "Invalid expression -> Mismached brackets: too many '('";
		numbers.Push(OM.Apply(operations.Pop(), numbers.Pop(), numbers.Pop()));
	}

	if (numbers.Empty())
		throw "Nothing was calculated!";

	double result = numbers.Pop();

	if (!numbers.Empty())
		throw "Invalid expression -> Some numbers left";

	return result;
}

int main(int argc, char* argv[]) {

	//argv[2] = "E:\\GitHub\\DSA-Homework\\DSA-Homework\\Debug\\Tests\\advancedTest.txt";
	//argv[1] = "31 a ( 5 b 32 f 10 e -230 ) c 324 d 17";
	//argc = 3;

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
