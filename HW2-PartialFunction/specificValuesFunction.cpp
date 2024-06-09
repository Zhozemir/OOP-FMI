// made with 0MI0700270

#include "specificValuesFunction.h"

FuncWithSpecificValues::FuncWithSpecificValues(const int32_t* results, const int32_t* values, int32_t count) : Func(results, count) {

    _values = new int32_t[count];

    for (size_t i = 0; i < count; i++) {

        _values[i] = values[i];

    }
}

void FuncWithSpecificValues::copyFrom(const FuncWithSpecificValues& other) {

    _values = new int32_t[other._count];

    for (size_t i = 0; i < other._count; i++) {

        _values[i] = other._values[i];

    }
}

void FuncWithSpecificValues::moveFrom(FuncWithSpecificValues&& other) {

    _values = other._values;
    other._values = nullptr;

}

void FuncWithSpecificValues::free() {

    delete[] _values;
    _values = nullptr;

}
FuncWithSpecificValues::FuncWithSpecificValues(const FuncWithSpecificValues& other) : Func(other) {

    copyFrom(other);

}

FuncWithSpecificValues& FuncWithSpecificValues::operator=(const FuncWithSpecificValues& other) {

    if (this != &other) {

        free();
        Func::operator=(other);
        copyFrom(other);

    }

    return *this;
}
FuncWithSpecificValues::FuncWithSpecificValues(FuncWithSpecificValues&& other) : Func(std::move(other)) {

    moveFrom(std::move(other));

}

FuncWithSpecificValues& FuncWithSpecificValues::operator=(FuncWithSpecificValues&& other) {

    if (this != &other) {

        free();
        Func::operator=(std::move(other));
        moveFrom(std::move(other));

    }

    return *this;
}
FuncWithSpecificValues::~FuncWithSpecificValues() {

    free();

}

bool FuncWithSpecificValues::isExcluded(int32_t point) const
{
    for (size_t i = 0; i < _count; i++){

        if (point == _results[i])
            return false;

    }

    return true;
}

int32_t FuncWithSpecificValues::operator()(int32_t point) const
{
    try {

        if (isExcluded(point)) {

            try {

                throw std::invalid_argument("this point is excluded");

            }
            catch (std::invalid_argument) {

                std::cout << "this point is excluded";

            }
        }

        for (size_t i = 0; i < _count; i++){

            if (point == _results[i])
                return _values[i];

        }
    }
    catch (std::invalid_argument) {

        std::cout << "this point is excluded";

    }
}

int32_t FuncWithSpecificValues::getLastDefinedPoint() const
{
    int32_t max = _results[0];

    for (size_t i = 0; i < _count; i++){
    
        if (max < _results[i])
            max = _results[i];

    }

    return max;
}


int32_t FuncWithSpecificValues::getFirstDefinedPoint() const
{
    int32_t min = _results[0];

    for (size_t i = 0; i < _count; i++){
    
        if (min > _results[i])
            min = _results[i];

    }

    return min;
}
