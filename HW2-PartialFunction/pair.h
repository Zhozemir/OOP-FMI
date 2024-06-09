// made with 0MI0700270

#pragma once
#include <cstdint>
#include <iostream>

class Pair {

	bool _isDefined;
	int32_t _value;

public:

	Pair();
	Pair(bool isDefined, int32_t value);
	void setValue(int32_t newValue);
	void setIsDefined(bool isDefined);
	bool getIsDefined() const;
	int32_t getValue() const;
};

std::ostream& operator<<(std::ostream& os, const Pair& pair);
