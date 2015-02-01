#include <iostream>

class Simulator {
public:
	Simulator(int rows, int cols, int waterQuantity);
	~Simulator();

	void iterate(double litersPerTick, size_t numberOfTicks);
	void printStatus(std::ostream& out) const;
	void setHeights(std::istream& in);
	void resetWater();

private:
	void operator=(const Simulator&);
	Simulator(const Simulator&);
	enum NeighbourType {
		lower,
		heigher,
		river
	};
	const double RIVER_CAPACITY;
	size_t rows;
	size_t cols;
	int permeability;
	size_t filledSorted;
	bool stableState;
	size_t stableStateAt;

	std::pair<size_t, size_t>* sortedVertices;
	int** heightsMap;
	double** waterMap;

	void putInSorted(size_t row, size_t col);
	void step(size_t row, size_t col, double waterInput);
	NeighbourType checkNeighbour(const std::pair<int, int>& coords, int height);
};