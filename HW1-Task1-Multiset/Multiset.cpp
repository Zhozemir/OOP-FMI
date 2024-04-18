#include "MultiSet.h"

MultiSet::MultiSet() {

    buckets = nullptr;
    bits = 0;
    maxNum = 0;

}

void MultiSet::copy(const MultiSet& other) {

    maxNum = other.maxNum;
    bits = other.bits;
    buckets = new uint8_t[maxNum];

    for (unsigned i = 0; i < maxNum; ++i) {

        buckets[i] = other.buckets[i];

    }
}

void MultiSet::free() {

    delete[] buckets;
    buckets = nullptr;

}

MultiSet::MultiSet(unsigned maxNum, uint8_t bits) {

    this->maxNum = maxNum;
    this->bits = bits;
    buckets = new uint8_t[maxNum];

    for (unsigned i = 0; i < maxNum; ++i) {

        buckets[i] = 0;

    }
}

MultiSet::MultiSet(const MultiSet& other) {

    copy(other);

}

MultiSet& MultiSet::operator=(const MultiSet& other) {

    if (this != &other) {

        free();
        copy(other);

    }

    return *this;
}

MultiSet::~MultiSet() {

    free();

}

void MultiSet::add(unsigned num) {

    if (num >= maxNum || buckets[num] >= (1 << bits) - 1)
        return;

    buckets[num]++;
}

bool MultiSet::contains(unsigned num) const {

    return num < maxNum && buckets[num] > 0;

}

unsigned MultiSet::countOccurrences(unsigned num) const {

    if (num >= maxNum) {
        return 0;
    }

    return buckets[num];

}

void MultiSet::print() const {

    std::cout << "{ ";

    for (int i = 0; i < maxNum; i++) {

        for (int j = 0; j < buckets[i]; j++) {

            std::cout << i << " ";

        }
    }

    std::cout << "}" << std::endl;
}

void MultiSet::writeBin(std::ofstream& ofs) {

    if (!ofs.is_open()) {
        return;
    }

    ofs.write((const char*)&maxNum, sizeof(maxNum));
    ofs.write((const char*)&bits, sizeof(bits));

    ofs.write((const char*)buckets, sizeof(uint8_t) * maxNum + 1);

    ofs.close();
}

void MultiSet::readBin(std::ifstream& ifs) {

    if (!ifs.is_open()) {
        return;
    }

    unsigned size;
    ifs.read((char*)&size, sizeof(size));

    uint8_t bits;
    ifs.read((char*)&bits, sizeof(bits));

    delete[]this->buckets;

    this->buckets = new uint8_t[size];
    this->maxNum = size;

    ifs.read((char*)buckets, sizeof(uint8_t) * maxNum + 1);

    ifs.close();
}

void MultiSet::printLikeInMemory() const {

    for (int i = maxNum - 1; i >= 0; i--) {

        std::cout << (buckets[i] ? "1" : "0");

    }

    std::cout << std::endl;
}

MultiSet intersection (const MultiSet& lhs, const MultiSet& rhs) {

    unsigned minMaxNum = std::min(lhs.maxNum, rhs.maxNum);
    uint8_t minBits = std::min(lhs.bits, rhs.bits);
    MultiSet intersectionRes (minMaxNum, minBits);

    for (int i = 0; i < minMaxNum; i++) {

        if (lhs.contains(i) && rhs.contains(i)) {

            intersectionRes.buckets[i] = std::min(lhs.buckets[i], rhs.buckets[i]);

        }
    }

    return intersectionRes;
}

MultiSet difference(const MultiSet& lhs, const MultiSet& rhs) {

    MultiSet differenceRes (lhs.maxNum, lhs.bits);

    for (int i = 0; i < lhs.maxNum; i++) {

        if (lhs.contains(i) && (!rhs.contains(i) || lhs.buckets[i] > rhs.buckets[i])) {

            differenceRes.buckets[i] = lhs.buckets[i] - (rhs.contains(i) ? rhs.buckets[i] : 0);

        }
    }

    return differenceRes;
}

MultiSet complement(const MultiSet& mSet) {

    MultiSet complemented(mSet.maxNum, mSet.bits);

    for (int i = 0; i < mSet.maxNum; i++) {

        if (mSet.contains(i)) {

            complemented.buckets[i] = (1 << mSet.bits) - 1 - mSet.buckets[i];

        }
        else {

            complemented.buckets[i] = (1 << mSet.bits) - 1;

        }
    }
    return complemented;
}

int main() {
    // Create a MultiSet with maximum number 10 and each element can have up to 3 occurrences (2^2-1)
    MultiSet ms1(10, 2);

    // Add some elements to the MultiSet
    ms1.add(2);
    ms1.add(2);
    ms1.add(3);
    ms1.add(5);
    ms1.add(5);
    ms1.add(5);

    // Print the current state of MultiSet
    std::cout << "MultiSet ms1: ";
    ms1.print();

    // Print how the MultiSet is stored in memory
    std::cout << "Memory representation of ms1: ";
    ms1.printLikeInMemory();

    // Create another MultiSet for operations
    MultiSet ms2(10, 2);
    ms2.add(3);
    ms2.add(5);
    ms2.add(5);

    std::cout << "MultiSet ms2: ";
    ms2.print();

    // Intersect ms1 and ms2
    MultiSet intersectionRes = intersection (ms1, ms2);
    std::cout << "Intersection of ms1 and ms2: ";
    intersectionRes.print();

    // Difference ms1 - ms2
    MultiSet differenceRes = difference (ms1, ms2);
    std::cout << "Difference (ms1 - ms2): ";
    differenceRes.print();

    // Complement of ms1
    MultiSet complemented = complement(ms1);
    std::cout << "Complement of ms1: ";
    complemented.print();

    // Serialization of ms1
    std::ofstream ofs("multiset.bin", std::ios::binary);
    ms1.writeBin(ofs);
    ofs.close();

    // Deserialization into ms3
    MultiSet ms3;
    std::ifstream ifs("multiset.bin", std::ios::binary);
    ms3.readBin(ifs);
    ifs.close();

    std::cout << "Deserialized MultiSet ms3: ";
    ms3.print();

    return 0;
}