// made with 0MI0700270

#pragma once
#include "minAndMaxPartial.hpp"

template<class ReturnType>
class MaxPartialFunction : public MinAndMaxPartialFunction<ReturnType> {

public:

	MaxPartialFunction();
	MaxPartialFunction(const PartialFunction<ReturnType>** functions, size_t functionsCount);
	virtual PartialFunction<ReturnType>* clone() const override;
	virtual ReturnType operator()(int32_t point) const override;

};

template<class ReturnType>
MaxPartialFunction<ReturnType>::MaxPartialFunction() : MinAndMaxPartialFunction<ReturnType>() {}

template<class ReturnType>
MaxPartialFunction<ReturnType>::MaxPartialFunction(const PartialFunction<ReturnType>** functions, size_t functionsCount) : MinAndMaxPartialFunction<ReturnType>(functions, functionsCount) {};

template<class ReturnType>
ReturnType MaxPartialFunction<ReturnType>::operator()(int32_t point) const {

	ReturnType max = this->_functions[0]->operator()(point);

	for (size_t i = 1; i < this->count; i++){
	
		ReturnType currentValue = this->_functions[i]->operator()(point);

		if (max.getValue() < currentValue.getValue()) {

			max = currentValue;

		}
	}

	return max;
}

template<class ReturnType>
PartialFunction<ReturnType>* MaxPartialFunction<ReturnType>::clone() const {

	return new MaxPartialFunction(*this);

}
