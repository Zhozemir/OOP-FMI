// made with 0MI0700270

#pragma once
#include "minAndMaxPartial.hpp"

template<class ReturnType>
class MinPartialFunction : public MinAndMaxPartialFunction<ReturnType> {

public:

	MinPartialFunction();
	MinPartialFunction(const PartialFunction<ReturnType>** functions, size_t functionsCount);
	virtual PartialFunction<ReturnType>* clone() const override;
	virtual ReturnType operator()(int32_t point) const override;
};

template<class ReturnType>
MinPartialFunction<ReturnType>::MinPartialFunction() : MinAndMaxPartialFunction<ReturnType>() {}

template<class ReturnType>
MinPartialFunction<ReturnType>::MinPartialFunction(const PartialFunction<ReturnType>** functions, size_t functionsCount) : MinAndMaxPartialFunction<ReturnType>(functions, functionsCount) {};

template<class ReturnType>
ReturnType MinPartialFunction<ReturnType>::operator()(int32_t point) const {

	ReturnType min = this->_functions[0]->operator()(point);

	for (size_t i = 1; i < this->count; i++){

		ReturnType currentValue = this->_functions[i]->operator()(point);

		if (min.getValue() > currentValue.getValue()) {

			min = currentValue;

		}

	}

	return min;
}

template<class ReturnType>
PartialFunction<ReturnType>* MinPartialFunction<ReturnType>::clone() const {

	return new MinPartialFunction(*this);

}
