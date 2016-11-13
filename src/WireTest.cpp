#include "WireTest.h"

#include <FS.h>  // Apparently this needs to be first
#include <OneWire.h>
#include <DallasTemperature.h>
#include "IicLcd.h"

#include "OneWireTest.h"


IIClcd LCDDisplay(0x27, 20, 4);

void relay_test()
{
    Serial.println("Beginning relay test...");
    LCDDisplay.clear();
    LCDDisplay.printAt_P(0,0,"Relay Test:");

    Serial.println("Turning on 'cool' for 10 seconds");
    LCDDisplay.printAt_P(0,1,"Turning 'cool' on");
    digitalWrite(coolingPin, LOW);
    delay(10000);
    Serial.println("Turning off 'cool' and waiting for 5 seconds");
    digitalWrite(coolingPin, HIGH);
    LCDDisplay.printAt_P(0,1,"Wait - Cool off  ");
    delay(5000);

    Serial.println("Turning on 'heat' for 10 seconds");
    LCDDisplay.printAt_P(0,1,"Turning 'heat' on");
    digitalWrite(heatingPin, LOW);
    delay(10000);
    Serial.println("Turning off 'heat' and waiting for 5 seconds");
    digitalWrite(heatingPin, HIGH);
    LCDDisplay.printAt_P(0,1,"Wait - Heat off  ");
    delay(5000);


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
    relay_test();
    run_temp_test(LCDDisplay);

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
}

void loop()
{
    // Do nothing.
    delay(2000);

}