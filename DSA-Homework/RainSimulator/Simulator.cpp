#include "Simulator.h"
#include <iomanip>
#include "List.h"
Simulator::Simulator(int rows, int cols, int permeability): RIVER_CAPACITY(2 * permeability){
	this->rows = rows;
	this->cols = cols;
	this->permeability = permeability;
	filledSorted = 0;
	this->sortedVertices = new std::pair<size_t, size_t>[rows * cols];
	
	this->heightsMap = new int*[rows];
	this->waterMap = new double*[rows];
	for (size_t i = 0; i < this->rows; i++) {
		heightsMap[i] = new int[cols];
		waterMap[i] = new double[cols];
		for (size_t j = 0; j < this->cols; j++) {
			waterMap[i][j] = 0;
		}
	}

	stableState = false;
	stableStateAt = 0;
}

Simulator::~Simulator() {
	delete [] sortedVertices;
	for (size_t i = 0; i < rows; i++) {
		delete heightsMap[i];
		delete waterMap[i];
	}
	delete heightsMap;
	delete waterMap;
}

void Simulator::printStatus(std::ostream& out) const {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			out << std::setw(5) << std::fixed << std::setprecision(2) << waterMap[i][j] << " ";
		}
		out << "\n";
	}
	/*if (stableState)
		out << "Stable state reached at iteration: " << stableStateAt << "\n";
	*/
}

void Simulator::resetWater() {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			waterMap[i][j] = 0;
		}
	}
	stableState = false;
	stableStateAt = 0;
}

void Simulator::setHeights(std::istream& in) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			in >> heightsMap[i][j];
			putInSorted(i, j);
		}
	}
}

void Simulator::putInSorted(size_t row, size_t col) {
	if (filledSorted == 0) {
		sortedVertices[0] = std::pair<size_t, size_t>(row, col);
		++filledSorted;
		return;
	}
	// Insertion sort idea

	std::pair<size_t, size_t>* current;
	size_t i = 0;
	while (i < filledSorted) {
		current = &sortedVertices[i];
		if (heightsMap[row][col] > heightsMap[current->first][current->second]) {
			for (size_t j = filledSorted; j > i; j--) {
				sortedVertices[j] = sortedVertices[j - 1];
			}
			break;
		}
		++i;
	}

	sortedVertices[i] = std::pair<int, int>(row, col);
	++filledSorted;
}

void Simulator::step(size_t row, size_t col, double waterInput) {
	//waterMap[row][col] += waterInput;
	double currentState = waterMap[row][col]; 
	std::pair<int, int> neighbours[4] = {
		std::pair<int, int>(row - 1, col),
		std::pair<int, int>(row, col + 1),
		std::pair<int, int>(row + 1, col),
		std::pair<int, int>(row, col - 1)
	};

	double capacity = 0;
	List<std::pair<int, int>> lowerNeighbours, riverNeighbours;

	NeighbourType type;
	for each (std::pair<int, int>& neighbour in neighbours) {
		type = checkNeighbour(neighbour, heightsMap[row][col]);
		if (type == NeighbourType::lower) {
			capacity += permeability;
			lowerNeighbours.PushBack(neighbour);
		}
		else if (type == NeighbourType::river) {
			capacity += RIVER_CAPACITY;
			riverNeighbours.PushBack(neighbour);
		}
	}

	// DEBUG 
	/*std::cout << "Lower neighbours of [" << row << "][" << col << "]: ";
	while (!lowerNeighbours.IsEmpty()) {
		std::cout << "[" << lowerNeighbours.Front().first << "][" << lowerNeighbours.Front().second << "] ";
		lowerNeighbours.PopFront();
	}*/

	double cellOutputPerNeighbour = waterMap[row][col] / (lowerNeighbours.Size() + riverNeighbours.Size());
	if (cellOutputPerNeighbour <= permeability) {
		// water splits equally in all directions
		waterMap[row][col] -= cellOutputPerNeighbour * riverNeighbours.Size();
		
		while (!lowerNeighbours.IsEmpty()) {
			std::pair<int, int>& neighbour = lowerNeighbours.Front();
			waterMap[neighbour.first][neighbour.second] += cellOutputPerNeighbour;
			waterMap[row][col] -= cellOutputPerNeighbour;
			lowerNeighbours.PopFront();
		}
	}
	else {
		// water per street is too much
		while (!lowerNeighbours.IsEmpty()) {
			std::pair<int, int>& neighbour = lowerNeighbours.Front();
			waterMap[neighbour.first][neighbour.second] += permeability;
			waterMap[row][col] -= permeability;
			lowerNeighbours.PopFront();
		}

		if (!riverNeighbours.IsEmpty()) {
			waterMap[row][col] -= riverNeighbours.Size() * RIVER_CAPACITY;

			if (waterMap[row][col] < 0)
				waterMap[row][col] = 0;
		}
	}

	if (currentState != waterMap[row][col])
		stableState = false;
	
}

void Simulator::iterate(double litersPerTick, size_t ticksCount) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			waterMap[i][j] += litersPerTick;
		}
	}

	for (size_t c = 0; c < ticksCount; c++) {
		stableState = true;
		for (size_t i = 0; i < filledSorted; i++) {
			step(sortedVertices[i].first, sortedVertices[i].second, litersPerTick);
		}
		if (stableState == true) {
			stableStateAt = c;
			break;
		}
	}
}

Simulator::NeighbourType Simulator::checkNeighbour(const std::pair<int, int> &coords, int height) {
	if (coords.first < 0 || coords.second < 0 || coords.first >= rows || coords.second >= cols)
		return NeighbourType::river;

	if (heightsMap[coords.first][coords.second] >= height)
		return NeighbourType::heigher;

	return NeighbourType::lower;
}