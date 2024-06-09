// made with 0MI0700270

#pragma once
#include "PartialFunction.hpp"

//const int32_t MAX_VALUE = INT32_MAX;
//const int32_t MIN_VALUE = INT32_MIN;

template<class ReturnType>
class MinAndMaxPartialFunction : public PartialFunction<ReturnType> {

	void copyFrom(const MinAndMaxPartialFunction<ReturnType>& other);
	void moveFrom(MinAndMaxPartialFunction<ReturnType>&& other);
	void free();

protected:

	PartialFunction<ReturnType>** _functions;
	size_t count;
	size_t cap;
	void resize(size_t newCap);

public:

	MinAndMaxPartialFunction();
	MinAndMaxPartialFunction(const PartialFunction<ReturnType>** functions, size_t functionsCount);
	MinAndMaxPartialFunction(const MinAndMaxPartialFunction<ReturnType>& other);
	MinAndMaxPartialFunction(MinAndMaxPartialFunction<ReturnType>&& other) noexcept;
	MinAndMaxPartialFunction& operator=(const MinAndMaxPartialFunction<ReturnType>& other);
	MinAndMaxPartialFunction& operator=(MinAndMaxPartialFunction<ReturnType>&& other) noexcept;
	virtual ~MinAndMaxPartialFunction() noexcept;
	void addFunction(PartialFunction<ReturnType>* function);
	virtual bool isDefined(int32_t point) const override;
	virtual int32_t getLastDefinedPoint() const override;
	virtual int32_t getFirstDefinedPoint() const override;
};

template<class ReturnType>
void MinAndMaxPartialFunction<ReturnType>::resize(size_t newCap){

	PartialFunction<ReturnType>** temp = new PartialFunction<ReturnType>*[newCap];

	for (size_t i = 0; i < count; i++){

		temp[i] = _functions[i]->clone();

	}

	free();
	_functions = temp;
	cap = newCap;
}

template<class ReturnType>
void MinAndMaxPartialFunction<ReturnType>::addFunction(PartialFunction<ReturnType>* function){

	if (count == cap)
		resize(cap * 2);
	_functions[count] = function;
	count++;

}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>::MinAndMaxPartialFunction(){

	cap = 8;
	_functions = new PartialFunction<ReturnType>*[cap];
	count = 0;

}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>::MinAndMaxPartialFunction(const PartialFunction<ReturnType>** functions, size_t functionsCount) : count(functionsCount), cap(functionsCount) {
	
	_functions = new PartialFunction<ReturnType>*[functionsCount];

	for (size_t i = 0; i < functionsCount; ++i) {

		_functions[i] = functions[i]->clone();

	}

}

template<class ReturnType>
void MinAndMaxPartialFunction<ReturnType>::free() {

	for (int i = 0; i < count; i++)
		delete _functions[i];

	delete[] _functions;

}

template<class ReturnType>
void MinAndMaxPartialFunction<ReturnType>::moveFrom(MinAndMaxPartialFunction<ReturnType>&& other){

	_functions = other._functions;
	other._functions = nullptr;

	count = other.count;
	cap = other.cap;

	other.count = other.cap = 0;
}

template<class ReturnType>
void MinAndMaxPartialFunction<ReturnType>::copyFrom(const MinAndMaxPartialFunction<ReturnType>& other){

	_functions = new PartialFunction<ReturnType> *[other.cap];

	for (int i = 0; i < other.count; i++)
		_functions[i] = other._functions[i]->clone();

	count = other.count;
	cap = other.cap;

}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>::MinAndMaxPartialFunction(const MinAndMaxPartialFunction<ReturnType>& other){

	copyFrom(other);

}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>::MinAndMaxPartialFunction(MinAndMaxPartialFunction<ReturnType>&& other) noexcept{

	moveFrom(std::move(other));

}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>& MinAndMaxPartialFunction<ReturnType>::operator= (const MinAndMaxPartialFunction<ReturnType>& other){

	if (this != &other){

		free();
		copyFrom(other);
	}

	return *this;
}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>& MinAndMaxPartialFunction<ReturnType>::operator=(MinAndMaxPartialFunction<ReturnType>&& other) noexcept{

	if (this != &other){

		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class ReturnType>
MinAndMaxPartialFunction<ReturnType>::~MinAndMaxPartialFunction() noexcept{

	free();

}

template<class ReturnType>
bool MinAndMaxPartialFunction<ReturnType>::isDefined(int32_t point) const {

	for (size_t i = 0; i < count; i++){

		if (!_functions[i]->isDefined(point))
			return false;

	}

	return true;
}

template<class ReturnType>
int32_t MinAndMaxPartialFunction<ReturnType>::getLastDefinedPoint() const{

	for (int32_t i = INT32_MAX; i >= INT32_MIN; i--){

		if (isDefined(i))
			return i;

	}

	return INT32_MIN;
}

template<class ReturnType>
int32_t MinAndMaxPartialFunction<ReturnType>::getFirstDefinedPoint() const{

	for (int32_t i = INT32_MIN; i <= INT32_MAX; i++){

		if (isDefined(i))
			return i;

	}

	return INT32_MAX;
}
