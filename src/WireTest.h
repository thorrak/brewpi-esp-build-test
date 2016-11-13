//
// Created by John Beeler on 11/12/16.
//

#ifndef BREWPI_ESP8266_WIRE_TEST_WIRETEST_H
#define BREWPI_ESP8266_WIRE_TEST_WIRETEST_H





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


#endif //BREWPI_ESP8266_WIRE_TEST_WIRETEST_H
