#pragma once

#include <fstream>
#include "Associativity.h"
#include <iostream>

class OperatorManager {
public:
	OperatorManager(std::ifstream& file);
	~OperatorManager();
	void Load(std::ifstream& file);

	// DEBUG ONLY
	void PrintOperators() {
		for (size_t i = 0; i < MAX_OPERATORS; i++) {
			if (operators[i])
				std::cout
				<< (char)i << " "
				<< operators[i]->operation << " "
				<< operators[i]->assoc << " "
				<< operators[i]->precedence
				<< std::endl;
		}
	}

	int GetPrecedence(char operation) const;
	Associativity GetAssociativity(char operation) const;
	double Apply(char operation, double lhs, double rhs) const;

private:
	void operator=(const OperatorManager&);
	OperatorManager(const OperatorManager&);
	OperatorManager();

	static const char OPERATIONS[];
	static const size_t MAX_OPERATORS;

	struct Operator {
		char operation;
		int precedence;
		Associativity assoc;
		Operator(char o, int p, int a);

	private:
		Operator();
		Operator(const Operator&);
		void operator=(const Operator&);
		bool inAllowedOperators(char o);
	};

	// Container for the operations -> O(1) indexing
	Operator** operators;
};