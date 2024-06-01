#include "SmartLight.h"
#include "SmartSpeaker.h"
#include "SmartThermostat.h"
#include "SmartHome.h";
#include "Device.h";

int main() {

    SmartHome home;

    SmartLight* light = new SmartLight("Light1", "Philips", 75);
    SmartSpeaker* speaker = new SmartSpeaker("Speaker1", "Sony", 50);
    SmartThermostat* thermostat = new SmartThermostat("Thermostat1", "Nest", 22, 24);

    home.addDevice(light);
    home.addDevice(speaker);
    home.addDevice(thermostat);

    std::cout << "All devices in the smart home:" << std::endl;
    std::cout << std::endl;
    home.printAllDevices();

    std::cout << "Speaker1 is removed!" << std::endl;
    std::cout << std::endl;
    home.removeDevice("Speaker1");

    std::cout << "All devices in the smart home after removal:" << std::endl;
    std::cout << std::endl;
    home.printAllDevices();

    return 0;
}
