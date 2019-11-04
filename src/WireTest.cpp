#include "WireTest.h"

#include <FS.h>  // Apparently this needs to be first
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <SPIFFS.h>
#endif

#include <OneWire.h>
#include <DallasTemperature.h>
#include "IicLcd.h"

#include "OneWireTest.h"
#include "RotaryEncoderTest.h"


IIClcd LCDDisplay(0x27, 20, 4);


void reset_wifi()
{
    /* reset_wifi() both resets the WiFi (by running Wifi.disconnect()) and reinitializes SPIFFS */

    // First, clear everything from serial/LCD
    LCDDisplay.clear();
    Serial.println();
    Serial.println();

    // Then reset the WiFi (should be quick)
    LCDDisplay.printAt_P(0,0,"Resetting WiFi");
    Serial.print("Disconnecting WiFi... ");
    WiFi.disconnect(true);
    delay(1000);  // Delay to give the radio time to do its thing

    if(WiFi.status() != WL_CONNECTED) {
        LCDDisplay.printAt_P(0,1,"...disconnected!");
        Serial.print("...disconnected!");
        delay(1000);
    } else {
        LCDDisplay.printAt_P(0,1,"...failed.");
        Serial.print("...failed.");
        delay(1000);
    }

    LCDDisplay.clear();

    // Next, reset (reinitialize) SPIFFS
    LCDDisplay.printAt_P(0,0,"Resetting SPIFFS");
    Serial.print("\r\n\r\nResetting SPIFFS...\r\n");
    LCDDisplay.printAt_P(0,1,"This may take 1min+");

    SPIFFS.begin();

    Serial.println("Please wait up to 30 secs for SPIFFS to be formatted");
    SPIFFS.format();
    Serial.println("Spiffs formatted!\r\n");
    LCDDisplay.printAt_P(0,2,"...done!");

    Serial.println("You can now disconnect your ESP and reflash with the final firmware.");

    delay(1000);
    LCDDisplay.clear();
}


void relay_test()
{
    Serial.println("Beginning relay test...");
    LCDDisplay.clear();
    LCDDisplay.printAt_P(0,0,"Relay Test:");

    Serial.println("Turning on 'cool' for 7 seconds");
    LCDDisplay.printAt_P(0,1,"Turning 'cool' on");
    digitalWrite(coolingPin, LOW);
    delay(7000);
    Serial.println("Turning off 'cool' and waiting for 3 seconds");
    digitalWrite(coolingPin, HIGH);
    LCDDisplay.printAt_P(0,1,"Wait - Cool off  ");
    delay(3000);

    Serial.println("Turning on 'heat' for 7 seconds");
    LCDDisplay.printAt_P(0,1,"Turning 'heat' on");
    digitalWrite(heatingPin, LOW);
    delay(7000);
    Serial.println("Turning off 'heat' and waiting for 3 seconds");
    digitalWrite(heatingPin, HIGH);
    LCDDisplay.printAt_P(0,1,"Wait - Heat off  ");
    delay(3000);


    Serial.println("Done with relay test!\r\n");
}


void LCD_test()
{
    Serial.println("Beginning LCD test...");
    LCDDisplay.printAt_P(0,0,"LCD initialized!");
    LCDDisplay.printAt_P(0,1,"Waiting 5 seconds!");
    Serial.println("LCD text printed! Waiting 5 seconds...\r\n");
    delay(5000);
}



void run_tests()
{
    delay(50);

    LCD_test();
    run_temp_test(LCDDisplay);
    relay_test();
    reset_wifi();
    LCDDisplay.clear();
    LCDDisplay.printAt_P(0,0,"Done with tests");

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
    LCDDisplay.init();
    LCDDisplay.updateBacklight();
    LCDDisplay.clear();


    run_tests();

    Serial.println("Dropping into rotary encoder test");
    rotaryenc_setup();


}

void loop()
{
    // Do nothing.
    //delay(2000);
    rotaryenc_loop();

}