#include "MultiSet.h"
#include <fstream>

int main() {

    MultiSet m(6, 4);
    m.add(1);
    std::cout << m.countOfNumber(1);
    std::cout << std::endl;

    m.print();
    m.add(1);
    std::cout << m.countOfNumber(1);
    std::cout << std::endl;

    m.print();
    m.add(1);
    std::cout << m.countOfNumber(1);
    std::cout << std::endl;

    m.print();
    std::cout << std::endl;



    m.add(2);
    m.add(2);
    m.add(2);
    m.add(2);
    m.add(2);
    std::cout << m.countOfNumber(2);
    std::cout << std::endl;
    m.print();

    m.multisetExtension(2);
    std::cout << m.countOfNumber(2);
    std::cout << std::endl;
    m.print();

    MultiSet m1(5, 3);

    m1.add(0);
    m1.add(1);
    m1.add(6);
    m1.add(4);


    int* difference = nullptr;
    unsigned sizeOfDif = 0;
    int* intersection = nullptr;
    unsigned sizeOfIntersect = 0;

    differenceOfSets(m, m1, difference, sizeOfDif);
    intersectionOfSets(m, m1, intersection, sizeOfIntersect);

    std::cout << std::endl;

    std::cout << "Intersection : ";
    for (size_t i = 0; i < sizeOfIntersect; i++)
    {
        std::cout << intersection[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "Difference : ";
    for (size_t i = 0; i < sizeOfDif; i++)
    {
        std::cout << difference[i] << " ";
    }

    std::cout << std::endl;

    std::ofstream ofs("multiset.dat", std::ios::binary);
    m.serialize(ofs);

    std::ifstream ifs("multiset.dat", std::ios::binary);
    m1.deserialize(ifs);
    m.print();
    m1.print();

    delete[] intersection;
    delete[] difference;
}