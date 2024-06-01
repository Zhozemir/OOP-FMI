#include "Device.h";

class SmartSpeaker : public Device {

	size_t volume = 0;


public:

	SmartSpeaker(const char* name, const char* proizvoditel, size_t volume);

	size_t getVolume();

	void setVolume(size_t volume);

	void turnOn() override;
	void turnOff() override;

	void printDetails() const override;

};