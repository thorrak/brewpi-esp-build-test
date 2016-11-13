
#ifndef BREWPI_ESP8266_WIRE_TEST_ONEWIRETEST_H
#define BREWPI_ESP8266_WIRE_TEST_ONEWIRETEST_H


#include "WireTest.h"
#include "IicLcd.h"
#include <OneWire.h>
#include <DallasTemperature.h>

void run_temp_test(IIClcd LCDDisplay);
void printAddress(DeviceAddress deviceAddress, IIClcd LCDDisplay);
void printTemperature(DeviceAddress deviceAddress, IIClcd LCDDisplay);
void print_temp_loop(IIClcd LCDDisplay);


#endif //BREWPI_ESP8266_WIRE_TEST_ONEWIRETEST_H
