#include "Device.h";

Device::Device(const char* name, const char* proizvoditel) {

	setName(name);
	setProizvoditel(proizvoditel);

}

Device::Device(const Device& other) {

	copyFrom(other);

}

Device& Device :: operator=(const Device& other) {

	if (this != &other) {


		copyFrom(other);

	}

	return *this;

}

Device :: ~Device() {

	free();

}

Device :: Device (Device&& other){

	moveFrom(std::move(other));

}

Device& Device :: operator= (Device&& other) {

   if (this != &other){
   
	   moveFrom(std::move(other));
   
   
   }

   return *this;

}

void Device::setName(const char* name) {

	if (name == nullptr || this->name == name)
		return;

	delete[] this->name;
	size_t nameLen = strlen(name);
	this->name = new char[nameLen + 1];
	strcpy(this->name, name);

}

void Device::setProizvoditel(const char* proizvoditel) {

	if (proizvoditel == nullptr || this->proizvoditel == proizvoditel)
		return;

	delete[] this->proizvoditel;
	size_t proizvoditelLen = strlen(proizvoditel);
	this->proizvoditel = new char[proizvoditelLen + 1];
	strcpy(this->proizvoditel, proizvoditel);


}

void Device::copyFrom(const Device& other) {

	name = new char[strlen(other.name)];
	strcpy(name, other.name);

	proizvoditel = new char[strlen(other.proizvoditel)];
	strcpy(proizvoditel, other.proizvoditel);

}

void Device::moveFrom(Device&& other) {

	name = other.name;
	other.name = nullptr;

	proizvoditel = other.proizvoditel;
	other.proizvoditel = nullptr;

}

void Device::free() {

	delete[] name;
	delete[] proizvoditel;

}


const char* Device::getName() const {

	return name;

}

const char* Device::getProizvoditel() const{

	return proizvoditel;

}

