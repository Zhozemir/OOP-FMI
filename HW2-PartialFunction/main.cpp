// made with 0MI0700270


#include <iostream>
#include <fstream>
#include "PartialFunction.hpp"
#include "FuncFactory.cpp"

void firstMode(PartialFunction<Pair>* function) {

    std::cout << "a: ";
    int32_t a;
    std::cin >> a;
    std::cout << std::endl;

    std::cout << "b: ";
    int32_t b;
    std::cin >> b;
    std::cout << std::endl;

    for (size_t i = a; i <= b; i++){
    
        if (function->isDefined(i))
            std::cout << "f(" << i << ") : " << function->operator()(i) << std::endl;
        else
            std::cout << "f is not defined for " << i << std::endl;
    }
}

void printNextPoint(PartialFunction<Pair>* function, int32_t& current, int32_t last) {

    for (int32_t i = current; i <= last; i++){

        if (function->isDefined(i)) {

            std::cout << "f(" << i << ") : " << function->operator()(i) << std::endl;
            current = ++i;
            break;


        }
    }
}

void secondMode(PartialFunction<Pair>* function) {

    unsigned short choice = 1;
    int32_t current = function->getFirstDefinedPoint();
    int32_t last = function->getLastDefinedPoint(); 

    while (choice) {

        printNextPoint(function, current, last);

        if (current > last)
            break;

        std::cout << "Enter 1 for next point or 0 for exit";
        std::cin >> choice;

    }
}

int main() {

    try {

        unsigned short modeOfWork;
        std::cout << "Choose mode 1 or mode 2: " << std::endl;
        std::cin >> modeOfWork;
        std::cout << std::endl;

        std::ifstream ifs("h2_3.bin", std::ios::binary);

        if (!ifs) {
            throw std::exception("Unable to open stream");
        }

        PartialFunction<Pair>* function = FuncFactory(ifs);

        switch (modeOfWork) {

        case 1: firstMode(function); break;
        case 2: secondMode(function); break;
        default: throw std::invalid_argument("Incorect Mode");

        }

        delete function;
    }

    catch (std::invalid_argument) {
        std::cout << "Incorect Mode";
    }
    catch (std::exception) {
        std::cout << "Unable to load the stream";
    }
}