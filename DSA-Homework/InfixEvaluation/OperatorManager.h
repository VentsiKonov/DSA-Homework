#pragma once

#include <fstream>
#include "Associativity.h"
#include <iostream>

class OperatorManager {
	
private:
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

	void operator=(const OperatorManager&);
	OperatorManager(const OperatorManager&);
	OperatorManager();

public:
	OperatorManager(std::ifstream& file);
	~OperatorManager();
	void Load(std::ifstream& file);
	
	// DEBUG ONLY
	void PrintOperators() {
		for (size_t i = 0; i < MAX_OPERATORS; i++) {
			if (operators[i])
				std::cout 
				<< (char)(i+65) << " " 
				<< operators[i]->operation << " "
				<< operators[i]->assoc << " " 
				<< operators[i]->precedence 
				<< std::endl;
		}
	}

	int GetPrecedence(char operation);
	Associativity GetAssociativity(char operation);
	void Apply(char operation);
};