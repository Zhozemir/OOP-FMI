#include "Device.h";

class SmartHome {

	Device** devices;
	size_t size;
	size_t capacity;

	void copyFrom(const SmartHome& other);
	void moveFrom(SmartHome&& other);

	void free();
	void resize(size_t newCapacity);


public: 

	SmartHome () = default;
	SmartHome(Device** devices, size_t size, size_t capacity);
	SmartHome(const SmartHome& other);
	SmartHome& operator= (const SmartHome& other);
	~SmartHome();


	SmartHome(SmartHome&& other);
	SmartHome& operator= (SmartHome&& other);

	void addDevice(Device* newDevice);
	void removeDevice(const char* deviceName);
	void printAllDevices() const;

	//Device& operator[](unsigned index) const;

};