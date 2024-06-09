// made with 0MI0700270


#include "PartialFunction.hpp"

template<class Function, class ReturnType>
class PartialFunctionByCriteria : public PartialFunction<ReturnType> {
	Function func;
public:
	PartialFunctionByCriteria() = default;
	PartialFunctionByCriteria(const Function& function);
	virtual bool isDefined(int32_t point) const override;
	virtual ReturnType operator()(int32_t point) const override;
	virtual PartialFunction<ReturnType>* clone() const override;
	virtual int32_t getLastDefinedPoint() const override;
	virtual int32_t getFirstDefinedPoint() const override;
};

template<class Function, class ReturnType>
PartialFunctionByCriteria<Function, ReturnType>::PartialFunctionByCriteria(const Function& function) : func(function) {}


template<class Function, class ReturnType>
bool PartialFunctionByCriteria<Function, ReturnType>::isDefined(int32_t point) const {

	return !func.isExcluded(point);

}

template<class Function, class ReturnType>
ReturnType PartialFunctionByCriteria<Function, ReturnType>::operator()(int32_t point) const{

	return ReturnType(isDefined(point),func(point));

}

template<class Function, class ReturnType>
PartialFunction<ReturnType>* PartialFunctionByCriteria<Function, ReturnType>::clone() const {

	return new PartialFunctionByCriteria<Function, ReturnType>(*this);

}

template<class Function, class ReturnType>
int32_t PartialFunctionByCriteria<Function, ReturnType>::getLastDefinedPoint() const{

	return func.getLastDefinedPoint();

}

template<class Function, class ReturnType>
int32_t PartialFunctionByCriteria<Function, ReturnType>::getFirstDefinedPoint() const{

	return func.getFirstDefinedPoint();

}
