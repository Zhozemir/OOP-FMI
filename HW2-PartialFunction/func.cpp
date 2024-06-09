// made with 0MI0700270

#include "Func.h"
#include <iostream>

Func::Func(const int32_t* results, int32_t count){

    _results = new int32_t[count];
    for (size_t i = 0; i < count; i++) {
        _results[i] = results[i];
    }
    _count = count;

}

void Func::copyFrom(const Func& other) {

    _results = new int32_t[other._count];

    for (size_t i = 0; i < other._count; i++) {

        _results[i] = other._results[i];

    }

    _count = other._count;
}

void Func::moveFrom(Func&& other) {

    _results = other._results;
    other._results = nullptr;
    _count = other._count;
    other._count = 0;

}

void Func::free() {

    delete[] _results;
    _results = nullptr;

}
Func::Func(const Func& other) {

    copyFrom(other);

}

Func& Func::operator=(const Func& other) {

    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}
Func::Func(Func&& other) noexcept {

    moveFrom(std::move(other));

}

Func& Func::operator=(Func&& other) noexcept {

    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}
Func::~Func() {

    free();

}

int32_t Func::getCount() const{

    return _count;

}

const int32_t* Func::getResults() const{

    return _results;

}

int32_t Func::getLastDefinedPoint() const{

    return MAX_VALUE;

}
int32_t Func::getFirstDefinedPoint() const{

    return MIN_VALUE;

}
