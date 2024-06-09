// made with 0MI0700270

#include "Pair.h"

Pair::Pair() : _value(0), _isDefined(false) {};

Pair::Pair(bool isDefined, int32_t value) : _value(value), _isDefined(isDefined) {};

void Pair::setValue(int32_t value) {

	_value = value;
	setIsDefined(true);

}
void Pair::setIsDefined(bool isDefined) {

	_isDefined = isDefined;

}
bool Pair::getIsDefined() const {

	return _isDefined;

}
int32_t Pair::getValue() const {

	return _value;

}
std::ostream& operator<<(std::ostream& os, const Pair& pair) {

	return os << "(" << pair.getIsDefined() << ", " << pair.getValue() << ")" << std::endl;

}
