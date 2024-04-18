#include <iostream>
#include <fstream>

class MultiSet {
private:
    uint8_t* buckets;
    uint8_t bits;
    unsigned maxNum;

    void copy(const MultiSet& other);
    void free();

public:
    MultiSet();
    MultiSet(unsigned maxNum, uint8_t bits);
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    void add(unsigned num);
    bool contains(unsigned num) const;
    unsigned countOccurrences(unsigned num) const;
    void print() const;
    void writeBin(std::ofstream& ofs);
    void readBin(std::ifstream& ifs);
    void printLikeInMemory() const;


    friend MultiSet intersection (const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet difference (const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet complement (const MultiSet& mSet);
    
};
