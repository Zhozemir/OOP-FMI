// made with 0MI0700270

#include "excludedPointsFunction.h"

FuncWithExcludedPoints::FuncWithExcludedPoints(const int32_t* results, int32_t count) : Func(results, count) {}

bool FuncWithExcludedPoints::isExcluded(int32_t point) const{

    for (size_t i = 0; i < _count; i++){

        if (point == _results[i])
            return true;

    }

    return false;
}

int32_t FuncWithExcludedPoints::operator()(int32_t point) const{

    if (isExcluded(point))
        throw std::invalid_argument("this point is excluded");

    return point;
}
