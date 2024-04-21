#include <iostream>

class MultiSet
{

private:

	uint8_t* _buckets = nullptr;
	unsigned _bucketsCount = 0;
	unsigned _n = 0;
	unsigned _k = 0;
	const unsigned _elementsInBucket = sizeof(uint8_t) * 8;

	void free();
	void copyFrom(const MultiSet& other);


	unsigned getBucketIndex(unsigned number) const;
	bool isInOneBucket(unsigned startIndex) const;
	unsigned getNumberStartIndex(unsigned num) const;
	void getAllAvailable(int*& numbers, unsigned& size) const;
	unsigned getCountOfAllNumbers() const;

public:

	MultiSet() = default;
	MultiSet(unsigned n, unsigned k, unsigned bucketsCount, uint8_t* buckets);
	MultiSet(unsigned n, unsigned k);

	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void add(unsigned num);
	void print() const;
	unsigned countOfNumber(unsigned num) const;
	void printAllAvailable() const;
	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
	void multisetExtension(int num);
	friend void intersectionOfSets(const MultiSet& lhs, const MultiSet& rhs, int*& result, unsigned& sizeOfResult);
	friend void differenceOfSets(const MultiSet& lhs, const MultiSet& rhs, int*& result, unsigned& sizeOfResult);;
};
