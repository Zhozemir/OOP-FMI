#include "SmartThermostat.h";

SmartThermostat::SmartThermostat(const char* name, const char* proizvoditel, size_t currentTemperature, size_t wantedTemperature) : Device(name, proizvoditel)
{

	setCurrentTemperature(currentTemperature);
	setWantedTemperature(wantedTemperature);

}

void SmartThermostat::setCurrentTemperature(size_t currentTemperature) {

	this->currentTemperature = currentTemperature;

}

void SmartThermostat::setWantedTemperature(size_t wantedTemperature) {

	this->wantedTemperature = wantedTemperature;

}

size_t SmartThermostat::getCurrentTemperature() {

	return currentTemperature;

}

size_t SmartThermostat::getWantedTemperature() {

	return wantedTemperature;

}

void SmartThermostat::turnOn() {
	std::cout << "SmartThermostat is turned on.\n";
}

void SmartThermostat::turnOff() {
	std::cout << "SmartThermostat is turned off.\n";
}

void SmartThermostat::printDetails() const {

	std::cout << "Name: " << getName() << std::endl << "Proizvoditel: " << getProizvoditel() << std::endl << "CurrentTempeature: " << currentTemperature << std::endl << "WantedTemperature: " << wantedTemperature;

}