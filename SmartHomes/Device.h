# pragma once;

#include <iostream>
#pragma warning (disable:4996)
#include <cstring>

class Device {

public: 

	Device(const char* name, const char* proizvoditel);
	Device(const Device& other);
	Device& operator= (const Device& other);
	virtual ~Device();

	Device(Device&& other);
	Device& operator=(Device&& other);

	const char* getName() const;
	const char* getProizvoditel() const;

	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
	virtual void printDetails() const = 0;

private:

	void copyFrom(const Device& other);
	void moveFrom(Device&& other);
	void free();


protected:

	char* name = nullptr;
	char* proizvoditel = nullptr;

	void setName(const char* name);
	void setProizvoditel(const char* proizvoditel);

};