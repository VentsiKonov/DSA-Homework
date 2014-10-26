#include "OperatorManager.h"

const size_t OperatorManager::MAX_OPERATORS = 256;
const char OperatorManager::OPERATIONS[] = {'+','-','/','*'};


OperatorManager::Operator::Operator(char o, int p, int a) {
	if (!inAllowedOperators(o)) {
		throw "Invalid operation";
	}
	if (!(a == 1 || a == 0)) {
		throw "Invalid associativity";
	}
	if (p < 0 || p > 10) {
		throw "Invalid precedence";
	}
	operation = o;
	precedence = p;
	assoc = a ? RIGHT : LEFT;
}

bool OperatorManager::Operator::inAllowedOperators(char o) {
	size_t len = strlen(OPERATIONS);
	for (size_t i = 0; i < len; i++) {
		if (OPERATIONS[i] == o)
			return true;
	}
	return false;
}


void OperatorManager::Load(std::ifstream& file) {
	unsigned char symbol;
	char operation;
	int precedence, assoc;

	while (file.good()) {
		file >> symbol
			 >> operation
			 >> precedence 
			 >> assoc;
			
		if (operators[symbol] != NULL)
			throw "Operation redefinition: " + symbol;

		try {
			operators[symbol] = new Operator(operation, precedence, assoc);
		}
		catch (std::bad_alloc) {
			throw "Not enough memory!";
		}
	}
}

Associativity OperatorManager::GetAssociativity(char operation) const {
	if (operators[operation])
		return operators[operation]->assoc;

	throw "No such operation: " + operation;
}

int OperatorManager::GetPrecedence(char operation) const {
	if (operators[operation])
		return operators[operation]->precedence;

	throw "No such operation: " + operation;
}

OperatorManager::OperatorManager(std::ifstream& file) {
	try {
		operators = new Operator*[MAX_OPERATORS];
	}
	catch (std::bad_alloc) {
		throw "No enough memory available!";
	}
	
	for (size_t i = 0; i < MAX_OPERATORS; i++) {
		operators[i] = NULL;
	}

	try {
		this->Load(file);
	}
	catch (const char* ex) {
		delete[] operators;
		std::cerr << "Error loading operators from file: " << ex;
	}
}

OperatorManager::~OperatorManager() {
	for (size_t i = 0; i < MAX_OPERATORS; i++) {
		delete operators[i];
	}
	delete operators;
}

double OperatorManager::Apply(char op, double lhs, double rhs) const {
	double result = 0;
	std::cout << lhs << op << rhs << '\n';
	switch (operators[op]->operation) {
		case '+':
			result = lhs + rhs;
			break;
		case '-':
			result = lhs - rhs;
			break;
		case '/':
			if (rhs == 0) 
				throw std::string("Division by zero! Operation: " + op).c_str();
			result = lhs / rhs;
			break;
		case '*':
			result = lhs * rhs;
			break;
		default:
			throw std::string("Unknown operation: " + op).c_str();
	}

	return result;
}