#include "Device.h";

class SmartThermostat : public Device {

	size_t currentTemperature = 0;
	size_t wantedTemperature = 0;


public:

	SmartThermostat(const char* name, const char* proizvoditel, size_t currentTemperature, size_t wantedTemperature);

	size_t getCurrentTemperature();
	size_t getWantedTemperature();

	void setCurrentTemperature(size_t currentTemperature);
	void setWantedTemperature(size_t wantedTemperature);

	void turnOn() override;
	void turnOff() override;

	void printDetails() const override;

};