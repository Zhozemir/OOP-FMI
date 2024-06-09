// made with 0MI0700270

#include <iostream>
#include <fstream>
#include "Func.h"
#include "specificValuesFunction.h"
#include "excludedPointsFunction.h"
#include "PartialFunctionByCriteria.hpp"
#include "PartialFunction.hpp"
#include "minAndMaxPartial.hpp"
#include "MinPartialFunction.hpp"
#include "MaxPartialFunction.hpp"
#include "Pair.h"
#include "oneOrZero.h"

static PartialFunction<Pair>* FuncFactoryByPath(const char* fileName);

static PartialFunction<Pair>* FuncFactory(std::ifstream& ifs)
{
    try {

        int16_t n;
        int16_t t;

        ifs.read((char*)(&n), sizeof(n));
        ifs.read((char*)(&t), sizeof(t));

        switch (t) {

        case 0: {

            int32_t* results = new int32_t[n];
            int32_t* values = new int32_t[n];

            ifs.read((char*)(results), n * sizeof(int32_t));
            ifs.read((char*)(values), n * sizeof(int32_t));
            FuncWithSpecificValues function(results, values, n);

            delete[] results;
            delete[] values;

            return new PartialFunctionByCriteria<FuncWithSpecificValues, Pair>(function);

        }
        case 1: {

            int32_t* excludedPoints = new int32_t[n];
            ifs.read((char*)(excludedPoints), n * sizeof(int32_t));
            FuncWithExcludedPoints function(excludedPoints, n);

            delete[] excludedPoints;

            return new PartialFunctionByCriteria<FuncWithExcludedPoints, Pair>(function);

        }
        case 2: {

            int32_t* valuesThatReturnsOne = new int32_t[n];
            ifs.read((char*)(valuesThatReturnsOne), n * sizeof(int32_t));
            FuncReturningOneOrZero function(valuesThatReturnsOne, n);

            delete[] valuesThatReturnsOne;

            return new PartialFunctionByCriteria<FuncReturningOneOrZero, Pair>(function);
        }
        case 3: {

            MinAndMaxPartialFunction<Pair>* res = new MaxPartialFunction<Pair>();

            for (size_t i = 0; i < n; i++){

                char buff[1024];
                ifs.getline(buff, 1024, '\0');
                size_t length = std::strlen(buff);
                PartialFunction<Pair>* func = FuncFactoryByPath(buff);
                res->addFunction(func);

            }

            return res;
        }
        case 4: {

            MinAndMaxPartialFunction<Pair>* res = new MinPartialFunction<Pair>();

            for (size_t i = 0; i < n; i++){
            
                char buff[1024];
                ifs.getline(buff, 1024, '\0');
                size_t length = std::strlen(buff);
                PartialFunction<Pair>* func = FuncFactoryByPath(buff);
                res->addFunction(func);

            }

            return res;
        }

        default:
            throw std::invalid_argument("Invalid T");
        }
    }
    catch (std::invalid_argument) {

        std::cout << "Invalid T";
        return nullptr;

    }
}
static PartialFunction<Pair>* FuncFactoryByPath(const char* fileName){

    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs) {

        try {
            throw std::exception("Unable to load the stream");
        }
        catch (std::exception) {
            std::cout << "Unable to load the stream";
        }
    }

    return FuncFactory(ifs);
}
