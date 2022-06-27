#include <Arduino.h>
#include "WireTest.h"

#include <FS.h>  // Apparently this needs to be first

#if defined(ESP8266)

#include <ESP8266WiFi.h>
#include <LittleFS.h>
#define FILESYSTEM LittleFS

#elif defined(ESP32_STOCK)

#include <WiFi.h>
#include <SPIFFS.h>
#define FILESYSTEM SPIFFS

#elif defined(ESP32S2)

#include <WiFi.h>
#include <LittleFS.h>
#define FILESYSTEM LittleFS

#else

#error "No valid filesystem selection found for this board type!"

#endif

#include <OneWire.h>

#include "LCDDisplay.h"
#include "OneWireTest.h"


IIClcd I2C_Display(0x27, 20, 4);
TFTDisplay TFT_Display;

LCDDisplay Display;


void reset_wifi()
{
    /* reset_wifi() both resets the WiFi (by running Wifi.disconnect()) and reinitializes SPIFFS/LittleFS */

    // First, clear everything from serial/LCD
    Display.clear();
    Serial.println();
    Serial.println();

    // Then reset the WiFi (should be quick)
    Display.printAt_P(0, 0, "Resetting WiFi");
    Serial.print("Disconnecting WiFi... ");
    WiFi.disconnect(true);
    delay(1000);  // Delay to give the radio time to do its thing

    if(WiFi.status() != WL_CONNECTED) {
        Display.printAt_P(0, 1, "...disconnected!");
        Serial.print("...disconnected!");
    } else {
        Display.printAt_P(0, 1, "...failed.");
        Serial.print("...failed.");
    }

    delay(1000);
    Display.clear();

    // Next, reset (reinitialize) SPIFFS/LittleFS
    Display.printAt_P(0, 0, "Resetting Filesystem");
    Serial.print("\r\n\r\nResetting Filesystem...\r\n");
    Display.printAt_P(0, 1, "This may take 1min+");

    FILESYSTEM.begin();

    Serial.println("Please wait up to 30 secs for filesystem to be formatted");
    FILESYSTEM.format();
    Serial.println("Filesystem formatted!\r\n");
    Display.printAt_P(0, 2, "...done!");

    Serial.println("You can now disconnect your ESP and reflash with the final firmware.");

    delay(1000);
    Display.clear();
}


void relay_test()
{
    Serial.println("Beginning relay test...");
    Display.clear();
    Display.printAt_P(0, 0, "Relay Test:");

    Serial.println("Turning on 'cool' for 7 seconds");
    Display.printAt_P(0, 1, "Turning 'cool' on");
    digitalWrite(coolingPin, LOW);
    delay(7000);
    Serial.println("Turning off 'cool' and waiting for 3 seconds");
    digitalWrite(coolingPin, HIGH);
    Display.printAt_P(0, 1, "Wait - Cool off  ");
    delay(3000);

    Serial.println("Turning on 'heat' for 7 seconds");
    Display.printAt_P(0, 1, "Turning 'heat' on");
    digitalWrite(heatingPin, LOW);
    delay(7000);
    Serial.println("Turning off 'heat' and waiting for 3 seconds");
    digitalWrite(heatingPin, HIGH);
    Display.printAt_P(0, 1, "Wait - Heat off  ");
    delay(3000);


    Serial.println("Done with relay test!\r\n");
}


void LCD_test()
{
    Serial.println("Beginning LCD test...");

    // Display.IICDisplay->printAt_P(0, 0, "LCD Initialized");
    Display.printAt_P(0, 0, "LCD initialized!");
    Display.printAt_P(0, 1, "Waiting 5 seconds!");
    Serial.println("LCD text printed! Waiting 5 seconds...\r\n");
    delay(5000);
}



void run_tests()
{
    delay(50);

    LCD_test();
    run_temp_test();
    relay_test();
    reset_wifi();
    Display.clear();
    Display.printAt_P(0, 0, "Done with tests");

}

void setup()
{

    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.print("Initializing pins... ");

    pinMode(heatingPin, OUTPUT);
    pinMode(coolingPin, OUTPUT);
    digitalWrite(coolingPin, HIGH);
    digitalWrite(heatingPin, HIGH);

    pinMode(doorPin, INPUT);        // We don't actually test doorPin for now, but leaving it here as a reminder
    Serial.println("Pins initialized!");


    Serial.println("Initializing LCD...");

    Display.IICDisplay = &I2C_Display;
    Display.TFT_Display = &TFT_Display;
    Display.init();
    Display.clear();


    run_tests();

}

void loop()
{
    // Do nothing.
    delay(2000);
}