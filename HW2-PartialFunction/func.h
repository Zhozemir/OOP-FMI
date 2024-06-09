// made with 0MI0700270

#pragma once
#include <cstdint>
#include <iostream>

const int32_t MAX_VALUE = INT32_MAX;
const int32_t MIN_VALUE = INT32_MIN;

class Func {

	void copyFrom(const Func& other);
	void free();
	void moveFrom(Func&& other);

protected:

	int32_t* _results;
	int32_t _count;

public:

	Func() = default;
	Func(const int32_t* results, int32_t count);
	Func(const Func& other);
	Func& operator=(const Func& other);
	Func(Func&& other) noexcept;
	Func& operator=(Func&& other) noexcept;
	virtual ~Func();

	int32_t getCount() const;
	const int32_t* getResults() const;

	virtual bool isExcluded(int32_t point) const = 0;
	virtual int32_t operator()(int32_t point) const = 0;
	virtual int32_t getLastDefinedPoint() const;
	virtual int32_t getFirstDefinedPoint() const;
};