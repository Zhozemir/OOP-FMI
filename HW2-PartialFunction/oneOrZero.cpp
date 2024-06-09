// made with 0MI0700270

#include "oneOrZero.h"

FuncReturningOneOrZero::FuncReturningOneOrZero(const int32_t* results, int32_t count) : Func(results, count) { }

bool FuncReturningOneOrZero::isExcluded(int32_t point) const{

    return false;

}

int32_t FuncReturningOneOrZero::operator()(int32_t point) const{

    for (size_t i = 0; i < _count; i++){

        if (point == _results[i])
            return 1;

    }

    return 0;
}
