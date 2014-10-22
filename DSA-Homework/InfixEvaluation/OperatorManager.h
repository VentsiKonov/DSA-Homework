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
		Operator(char o, int p, int a) {
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
	private:
		Operator();
		Operator(const Operator&);
		void operator=(const Operator&);
		bool inAllowedOperators(char o) {
			for (size_t i = 0; i < strlen(OPERATIONS); i++) {
				if (OPERATIONS[i] == o) return true;
			}
			return false;
		}
	};

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