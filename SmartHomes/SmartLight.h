#include "Device.h";

class SmartLight : public Device {

	size_t brightnessLevel = 0;


public: 

	SmartLight(const char* name, const char* proizvoditel, size_t brightnessLevel);

	size_t getBrightnessLevel() const;

	void setBrightnessLevel(size_t brightnessLevel);

	void turnOn() override;
	void turnOff() override;

	void printDetails() const override;

};