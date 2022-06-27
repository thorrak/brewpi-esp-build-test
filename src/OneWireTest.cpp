#include <Arduino.h>
#include "OneWireTest.h"
#include "LCDDisplay.h"


// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <sstream>

#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(oneWirePin);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;

extern LCDDisplay Display;

void run_temp_test()
{
    std::ostringstream s;

    Serial.println("Dallas Temperature IC Test");

    // Start up the library
    sensors.begin();

    // locate devices on the bus
    Serial.print("Locating devices...");
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" devices.");

    Display.clear();
    Display.printAt_P(0,0,"OneWire Test:");

    s << "Found " << (int) sensors.getDeviceCount() << " Devices";

    Display.printAt_P(0,3,s.str().c_str());

    // report parasite power requirements
    Serial.print("Parasite power is: ");
    if (sensors.isParasitePowerMode()) {
        // Parasite power mode isn't supported in BrewPi installations at the moment
        // This may be an arbitrary decision, but I'm assuming it creates issues for reading the temperature
        Serial.println("ON");
        Display.printAt_P(0,1,"Parasite ON!");
        Display.printAt_P(0,2,"This is not good!");
        Serial.println("Note - This isn't good. BrewPi doesn't support this configuration.");
        Serial.println("Please rewire your temperature sensors to have explicit +3.3v power in.");
        delay(2000);
    } else {
        Serial.println("OFF");
        Display.printAt_P(0,1,"Parasite Off");
    }

    Serial.println("Waiting 5 seconds before continuing");
    delay(5000);


    // Search for devices on the bus and assign based on an index. Ideally,
    // you would do this to initially discover addresses on the bus and then
    // use those addresses and manually assign them (see above) once you know
    // the devices on your bus (and assuming they don't change).
    //
    // method 1: by index
//    if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
//    if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");

    // method 2: search()
    // search() looks for the next device. Returns 1 if a new address has been
    // returned. A zero might mean that the bus is shorted, there are no devices,
    // or you have already retrieved all of them. It might be a good idea to
    // check the CRC to make sure you didn't get garbage. The order is
    // deterministic. You will always get the same devices in the same order
    //
    // Must be called before search()
    //oneWire.reset_search();
    // assigns the first address found to insideThermometer
    //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
    // assigns the seconds address found to outsideThermometer
    //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");

    Display.clear();
    Display.printAt_P(0,0,"OneWire Test:");

    uint8_t i = 0;
    while(oneWire.search(insideThermometer)) {

        Serial.print("Device ");
        Serial.print(i);
        Serial.print(" Address: ");

        s.str("");
        s.clear();
        s << "Device " << (int) i << " Address:";
        Display.printAt_P(0,1,s.str().c_str());

        printAddress(insideThermometer);
        sensors.requestTemperatures();
        delay(300);
        Serial.println();
        printTemperature(insideThermometer);

        delay(2700);

        i++;

    }

    delay(2000);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
    std::ostringstream s;

    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        if (deviceAddress[i] < 16) {
            Serial.print("0");
            s << "0";
        }
        Serial.print(deviceAddress[i], HEX);
        s << (int) deviceAddress[i];
    }

    Display.printAt_P(0,2,s.str().c_str());
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
    std::ostringstream s;
    s.precision(3);
    float tempC = sensors.getTempC(deviceAddress);
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.print(" Temp F: ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));

    s << "Temp C:" << tempC << ",F:" << DallasTemperature::toFahrenheit(tempC);
    Display.printAt_P(0,3,s.str().c_str());
}

//// function to print a device's resolution
//void printResolution(DeviceAddress deviceAddress)
//{
//    Serial.print("Resolution: ");
//    Serial.print(sensors.getResolution(deviceAddress));
//    Serial.println();
//}

//// main function to print information about a device
//void printData(DeviceAddress deviceAddress)
//{
//    Serial.print("Device Address: ");
//    printAddress(deviceAddress);
//    Serial.print(" ");
//    printTemperature(deviceAddress);
//    Serial.println();
//}
