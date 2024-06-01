#include "SmartLight.h";


SmartLight::SmartLight(const char* name, const char* proizvoditel, size_t brightnessLevel) : Device(name, proizvoditel)
{

	setBrightnessLevel(brightnessLevel);

}

void SmartLight::setBrightnessLevel(size_t brightnessLevel) {


	this->brightnessLevel = brightnessLevel;
   

}

size_t SmartLight::getBrightnessLevel() const {

	return brightnessLevel;

}

void SmartLight::turnOn() {
	std::cout << "SmartLight is turned on.\n";
}

void SmartLight::turnOff() {
	std::cout << "SmartLight is turned off.\n";
}

void SmartLight::printDetails() const {

	std::cout << "Name: " << getName() << std::endl << "Proizvoditel: " << getProizvoditel() << std::endl << "BrightnssLevel: " << brightnessLevel;

}