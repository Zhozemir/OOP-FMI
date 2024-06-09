// made with 0MI0700270

#pragma once
#include <cstdint>

template <class ReturnType>
class PartialFunction {

public:

	virtual ~PartialFunction() = default;
	virtual bool isDefined(int32_t point) const = 0;
	virtual ReturnType operator()(int32_t point) const = 0;
	virtual PartialFunction<ReturnType>* clone() const = 0;
	virtual int32_t getLastDefinedPoint() const = 0;
	virtual int32_t getFirstDefinedPoint() const = 0;
};
