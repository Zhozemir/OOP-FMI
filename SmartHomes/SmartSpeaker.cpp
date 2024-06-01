#include "SmartSpeaker.h";

SmartSpeaker::SmartSpeaker(const char* name, const char* proizviditel, size_t volume) : Device(name, proizviditel)
{

	setVolume(volume);

}

void SmartSpeaker::setVolume(size_t volume) {

	this->volume = volume;

}

size_t SmartSpeaker::getVolume() {

	return volume;

}

void SmartSpeaker::turnOn() {
	std::cout << "SmartSpeaker is turned on.\n";
}

void SmartSpeaker::turnOff() {
	std::cout << "SmartSpeaker is turned off.\n";
}

void SmartSpeaker::printDetails() const {

	std::cout << "Name: " << getName() << std::endl << "Proizvoditel: " << getProizvoditel() << std::endl << "Volume: " << volume;

}