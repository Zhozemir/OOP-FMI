#include <iostream>
#include "MultiSet.h";
#include <fstream>

MultiSet::MultiSet(unsigned n, unsigned k) {
    _bucketsCount = ((n + 1) * k) / _elementsInBucket + 1;
    _buckets = new uint8_t[_bucketsCount]{ 0 };
    _n = n + 1;
    _k = k;
}

void MultiSet::free() {
    delete[] _buckets;
    _bucketsCount = _n = _k = 0;
    _buckets = nullptr;
}

void MultiSet::copyFrom(const MultiSet& other) {
    _buckets = new uint8_t[other._bucketsCount];
    for (size_t i = 0; i < other._bucketsCount; i++)
    {
        _buckets[i] = other._buckets[i];
    }
    _bucketsCount = other._bucketsCount;
    _n = other._n;
    _k = other._k;
}

MultiSet::MultiSet(unsigned n, unsigned k, unsigned bucketsCount, uint8_t* buckets) {
    _buckets = new uint8_t[bucketsCount];
    for (size_t i = 0; i < bucketsCount; i++)
    {
        _buckets[i] = buckets[i];
    }
    _bucketsCount = bucketsCount;
    _n = _n;
    _k = _k;
}

MultiSet::MultiSet(const MultiSet& other) {
    copyFrom(other);
}
MultiSet& MultiSet::operator=(const MultiSet& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
MultiSet::~MultiSet()
{
    free();
}

unsigned MultiSet::getNumberStartIndex(unsigned num) const
{
    return _k * (num - 1);
}

bool MultiSet::isInOneBucket(unsigned startIndex) const {
    return startIndex / _elementsInBucket == (startIndex + _k - 1) / _elementsInBucket;
}

unsigned MultiSet::getBucketIndex(unsigned num) const
{
    return num / _elementsInBucket;
}

unsigned creatingMaskWithOnes(size_t start, size_t end) {
    unsigned mask = 0;
    for (size_t i = start; i < end; i++)
    {
        mask += (1 << i);
    }
    return mask;
}

void MultiSet::add(unsigned num)
{
    num++;
    if (num > _n) {
        return;
    }
    unsigned startIndexOfNumber = getNumberStartIndex(num);
    unsigned bucketIndex = getBucketIndex(startIndexOfNumber);
    if (isInOneBucket(startIndexOfNumber)) {
        uint8_t mask = 1 << _elementsInBucket - ((startIndexOfNumber + _k - 1) % _elementsInBucket) - 1;
        _buckets[bucketIndex] += mask;
    }
    else {
        unsigned elementsInFirstBucket = _elementsInBucket - (startIndexOfNumber % _elementsInBucket);
        unsigned elementsInSecondBucket = _k - elementsInFirstBucket;

        unsigned mask = 0;

        for (size_t i = _elementsInBucket - 1; i >= _elementsInBucket - elementsInSecondBucket; i--)
        {
            mask += (1 << i);
        }
        if (!((_buckets[bucketIndex + 1] & mask) == mask)) {
            _buckets[bucketIndex + 1] += (1 << (_elementsInBucket - elementsInSecondBucket));
            return;
        }

        _buckets[bucketIndex + 1] &= (~mask);
       
        mask = creatingMaskWithOnes(0, elementsInFirstBucket);
        if (!((_buckets[bucketIndex] & mask) == mask)) {
            _buckets[bucketIndex]++;
        }
    }
}

unsigned MultiSet::countOfNumber(unsigned num) const {
    num++;
    if (num > _n) {
        return 0;
    }
    unsigned startIndexOfNumber = getNumberStartIndex(num);
    unsigned bucketIndex = getBucketIndex(startIndexOfNumber);
    unsigned startIndexInTheBucket = startIndexOfNumber % _elementsInBucket;
    if (isInOneBucket(startIndexOfNumber)) {
        unsigned movedBucked = _buckets[bucketIndex] >> (_elementsInBucket - _k - startIndexInTheBucket);
        unsigned mask = creatingMaskWithOnes(0, _k);

        return (movedBucked & mask);
    }
    else {
        unsigned elementsInFirstBucket = _elementsInBucket - (startIndexOfNumber % _elementsInBucket);
        unsigned elementsInSecondBucket = _k - elementsInFirstBucket;
        unsigned mask = creatingMaskWithOnes(0, elementsInFirstBucket);;
        unsigned result = ((_buckets[bucketIndex] & mask) << elementsInSecondBucket); 

        unsigned movedBucked = _buckets[bucketIndex + 1] >> (_elementsInBucket - elementsInSecondBucket);
        mask = creatingMaskWithOnes(0, elementsInSecondBucket);
        return result + (movedBucked & mask);
    }


}

void MultiSet::printAllAvailable() const {
    std::cout << "{ ";
    for (size_t i = 0; i < _n; i++)
    {
        if (countOfNumber(i) > 0) {
            std::cout << i << ", ";
        }
    }
    std::cout << " }";
}

void printBinary(uint8_t num) {
    int size = sizeof(num) * 8;
    for (int i = size - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        std::cout << bit;
    }
}

void MultiSet::print() const
{
    for (size_t i = 0; i < _bucketsCount; i++)
    {
        printBinary(_buckets[i]);
        std::cout << std::endl;
    }
}

void MultiSet::serialize(std::ofstream& ofs) const {

    if (!ofs.is_open()) {
        return;
    }

    ofs.write((const char*)&_bucketsCount, sizeof(_bucketsCount));
    ofs.write((const char*)&_n, sizeof(_n));
    ofs.write((const char*)&_k, sizeof(_k));

    ofs.write((const char*)_buckets, sizeof(uint8_t) * _bucketsCount);

    ofs.close();
}

void MultiSet::deserialize(std::ifstream& ifs) {

    if (!ifs.is_open()) {
        return;
    }

    unsigned bucketsCount;
    ifs.read((char*)&bucketsCount, sizeof(bucketsCount));

    unsigned n;
    ifs.read((char*)&n, sizeof(n));

    unsigned k;
    ifs.read((char*)&k, sizeof(k));

    delete[]this->_buckets;

    this->_buckets = new uint8_t[bucketsCount];
    this->_bucketsCount = bucketsCount;
    this->_n = n;
    this->_k = k;

    ifs.read((char*)_buckets, sizeof(uint8_t) * bucketsCount);

    ifs.close();
}

unsigned MultiSet::getCountOfAllNumbers() const {
    unsigned result = 0;
    for (size_t i = 0; i < _n; i++)
    {
        if (countOfNumber(i) > 0) {
            result++;
        }
    }
    return result;
}

void MultiSet::getAllAvailable(int*& numbers, unsigned& size) const {
    size = getCountOfAllNumbers();
    numbers = new int[size];
    int current = 0;
    for (size_t i = 0; i < _n; i++)
    {
        if (countOfNumber(i) > 0) {
            numbers[current] = i;
            current++;
        }
    }
}

void intersectionOfSets(const MultiSet& lhs, const MultiSet& rhs, int*& result, unsigned& size)
{
    if (result) {
        delete[] result;
    }
    int* numbersInFirst = nullptr;
    size = 0;
    lhs.getAllAvailable(numbersInFirst, size);
    result = new int[size];
    unsigned curr = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (rhs.countOfNumber(numbersInFirst[i]) > 0) {
            result[curr] = numbersInFirst[i];
            curr++;
        }
    }
    for (size_t i = curr; i < size; i++)
    {
        result[i] = -1;
    }
    size = curr;
    delete[] numbersInFirst;
}

void differenceOfSets(const MultiSet& lhs, const MultiSet& rhs, int*& result, unsigned& size)
{
    if (result) {
        delete[] result;
    }
    int* numbersInFirst = nullptr;
    size = 0;
    lhs.getAllAvailable(numbersInFirst, size);
    result = new int[size];
    unsigned curr = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (rhs.countOfNumber(numbersInFirst[i]) == 0) {
            result[curr] = numbersInFirst[i];
            curr++;
        }
    }
    for (size_t i = curr; i < size; i++)
    {
        result[i] = -1;
    }
    size = curr;
    delete[] numbersInFirst;
}

void MultiSet::multisetExtension(int num) {
    num++;
    if (num > _n) {
        return;
    }
    unsigned startIndexOfNumber = getNumberStartIndex(num);
    unsigned bucketIndex = getBucketIndex(startIndexOfNumber);
    unsigned startIndexInTheBucket = startIndexOfNumber % _elementsInBucket;
    int mask = 0;
    if (isInOneBucket(startIndexOfNumber)) {
        mask = creatingMaskWithOnes(0, _k);
        _buckets[bucketIndex] ^= (mask << (_elementsInBucket - _k - startIndexInTheBucket));
    }
    else {
        unsigned elementsInFirstBucket = _elementsInBucket - (startIndexOfNumber % _elementsInBucket);
        unsigned elementsInSecondBucket = _k - elementsInFirstBucket;
        mask = creatingMaskWithOnes(0, elementsInSecondBucket);
        _buckets[bucketIndex + 1] ^= (mask << (_elementsInBucket - elementsInSecondBucket));
        mask = 0;
        mask = creatingMaskWithOnes(0, elementsInFirstBucket);
        _buckets[bucketIndex] ^= mask;
    }
}
