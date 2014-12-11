template<typename T>
class SortTester {
public:
	SortTester(Sorter<T> ** sorters, int count);
	virtual void getSummary(std::ostream & out);
};