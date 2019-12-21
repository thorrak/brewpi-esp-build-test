
#ifndef BREWPI_ESP8266_WIRE_TEST_ONEWIRETEST_H
#define BREWPI_ESP8266_WIRE_TEST_ONEWIRETEST_H


#include "WireTest.h"
#include "IicLcd.h"
#include <OneWire.h>
#include <DallasTemperature.h>

void run_temp_test();
void printAddress(DeviceAddress deviceAddress);
void printTemperature(DeviceAddress deviceAddress);
void print_temp_loop();


#endif //BREWPI_ESP8266_WIRE_TEST_ONEWIRETEST_H
