#include "OperatorManager.h"

const size_t OperatorManager::MAX_OPERATORS = 57;
const char OperatorManager::OPERATIONS[] = {'+','-','/','*'};

void OperatorManager::Load(std::ifstream& file) {
	char symbol, operation;
	int precedence, assoc;

	while (file.good()) {
		file >> symbol 
			 >> operation
			 >> precedence 
			 >> assoc;
			
		if (operators[symbol-65] != NULL)
			throw "Operation redefinition: " + symbol;

		operators[symbol-65] = new Operator(operation, precedence, assoc);
	}
}

Associativity OperatorManager::GetAssociativity(char operation) {
	if (operators[operation - 65])
		return operators[operation - 65]->assoc;

	throw "No such operation: " + operation;
}

int OperatorManager::GetPrecedence(char operation) {
	if (operators[operation - 65])
		return operators[operation - 65]->precedence;

	throw "No such operation: " + operation;
}



OperatorManager::OperatorManager(std::ifstream& file) {
	operators = new Operator*[MAX_OPERATORS];
	for (size_t i = 0; i < MAX_OPERATORS; i++) {
		operators[i] = NULL;
	}
	Load(file);
}

OperatorManager::~OperatorManager() {
	for (size_t i = 0; i < MAX_OPERATORS; i++) {
		delete operators[i];
	}
	delete operators;
}