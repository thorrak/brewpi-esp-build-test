//
// Created by John Beeler on 11/12/16.
//

#ifndef BREWPI_ESP8266_WIRE_TEST_WIRETEST_H
#define BREWPI_ESP8266_WIRE_TEST_WIRETEST_H



#if defined(ESP8266)

#define NODEMCU_PIN_A0 17	// Analog

#define NODEMCU_PIN_D0 16	// No interrupt, do not use for rotary encoder
#define NODEMCU_PIN_D1 5	// Generally used for I2C
#define NODEMCU_PIN_D2 4	// Generally used for I2C
#define NODEMCU_PIN_D3 0	// Has some degree of noise at startup
#define NODEMCU_PIN_D4 2    // Also controls the LED on the ESP8266 module
#define NODEMCU_PIN_D5 14
#define NODEMCU_PIN_D6 12
#define NODEMCU_PIN_D7 13
#define NODEMCU_PIN_D8 15

#define NODEMCU_PIN_D9 3	// Do not use - USB
#define NODEMCU_PIN_D10 1	// Do not use - USB



#define heatingPin NODEMCU_PIN_D0
#define coolingPin NODEMCU_PIN_D5

#define oneWirePin NODEMCU_PIN_D6
#define doorPin    NODEMCU_PIN_D7



#define IIC_SDA NODEMCU_PIN_D2
#define IIC_SCL NODEMCU_PIN_D1


#elif defined(ESP32)

#define heatingPin 25
#define coolingPin 26

// If oneWirePin is specified, beerSensorPin and fridgeSensorPin are ignored
#define oneWirePin 13  
#define doorPin    34  // Note - 34 is "input only" and shouldn't be repurposed

#define IIC_SDA 21
#define IIC_SCL 22


/*
connecting Rotary encoder
CLK (A pin) - to any microcontroler intput pin with interrupt -> in this example pin 32
DT (B pin) - to any microcontroler intput pin with interrupt -> in this example pin 21
SW (button pin) - to any microcontroler intput pin -> in this example pin 25
VCC - to microcontroler VCC (then set ROTARY_ENCODER_VCC_PIN -1) or in this example pin 25
GND - to microcontroler GND
*/
#define ROTARY_ENCODER_A_PIN 19
#define ROTARY_ENCODER_B_PIN 18
#define ROTARY_ENCODER_BUTTON_PIN 0
#define ROTARY_ENCODER_VCC_PIN -1 /*put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */


#endif


#endif //BREWPI_ESP8266_WIRE_TEST_WIRETEST_H
