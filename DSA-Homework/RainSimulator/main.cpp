#include <iostream>
#include "Simulator.h"
#include "List.h"
int main() {
	
	int rows, cols, permeability;
	std::cin >> rows >> cols >> permeability;
	Simulator sim(rows, cols, permeability);
	sim.setHeights(std::cin);

	List<std::pair<int, int>> cases;
	int casesCount, liters, ticks;
	std::cin >> casesCount;
	for (size_t i = 0; i < casesCount; i++) {
		std::cin >> liters >> ticks;
		cases.PushBack(std::pair<int, int>(liters, ticks));
	}

	while (!cases.IsEmpty()) {
		std::pair<int, int> current = cases.PopFront();
		sim.iterate(current.first, current.second);
		sim.printStatus(std::cout);
		std::cout << "\n";
		sim.resetWater();
	}

	return 0;
}

