#include "SmartHome.h";


SmartHome::SmartHome(Device** devices, size_t size, size_t capacity) {

	devices = new Device * [capacity];
	this->size = size;
	this->capacity = capacity;
	
}

SmartHome::SmartHome(const SmartHome& other) {

	copyFrom(other);

}

SmartHome& SmartHome::operator=(const SmartHome& other) {

	if (this != &other) {

     copyFrom(other);

	}

	return *this;
}

SmartHome :: ~SmartHome() {

	free();

}

SmartHome::SmartHome(SmartHome&& other) {

	moveFrom(std::move(other));

}

SmartHome& SmartHome :: operator= (SmartHome&& other) {

	if (this != &other) {
	
		free();
		moveFrom(std::move(other));
	
	}

	return *this;


}

void SmartHome::copyFrom(const SmartHome& other) {

	devices = new Device* [other.capacity];

	for (int i = 0; i < other.size; i++) {
	
		devices[i] = other.devices[i];
	
	}

	size = other.size;
	capacity = other.capacity;

}

void SmartHome::moveFrom(SmartHome&& other) {

	devices = other.devices;
	other.devices = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

}

void SmartHome::free() {

	for (int i = 0; i < size; i++) {
	
		delete devices[i];

	}

	delete[] devices;

}

void SmartHome::resize(size_t newCapacity) {

	Device** newDevices = new Device* [newCapacity];

	for (int i = 0; i < size; i++) {

		newDevices[i] = devices[i];

	}

		delete[] devices;
		devices = newDevices;
		capacity = newCapacity;

}

void SmartHome::addDevice(Device* device) {

	if (size >= capacity) {
		resize(capacity == 0 ? 1 : capacity * 2);
	}
	devices[size++] = device;

}

void SmartHome::removeDevice(const char* deviceName) {

	for (size_t i = 0; i < size; i++) {

		if (strcmp(devices[i]->getName(), deviceName) == 0) {
			delete devices[i];

			for (size_t j = i; j < size - 1; j++) {

				devices[j] = devices[j + 1];

			}

			devices[size--] = nullptr;
			return;

		}
	}
	std::cout << "Device not found." << std::endl;

}

void SmartHome::printAllDevices() const {

	for (int i = 0; i < size; i++) {
	
		devices[i]->printDetails();
		std::cout << std::endl;
		std::cout << std::endl;
	
	}

}




