//
// Created by John Beeler on 4/1/19.
//

#include "WireTest.h"
#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include "LCDDisplay.h"

#include <string>
#include <sstream>

extern LCDDisplay Display;

#if defined(ESP32)

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);

int test_limits = 2;

void rotary_onButtonClick() {
    //rotaryEncoder.disable();
    rotaryEncoder.setBoundaries(-test_limits, test_limits, false);
    test_limits *= 2;
    rotaryEncoder.reset();  // Reset the value to 0
}

void rotary_loop() {
    std::ostringstream s;

    //first lets handle rotary encoder button click
    if (rotaryEncoder.currentButtonState() == BUT_RELEASED) {
        //we can process it here or call separate function like:
        rotary_onButtonClick();
    }

    //lets see if anything changed
    int16_t encoderDelta = rotaryEncoder.encoderChanged();

    //optionally we can ignore whenever there is no change
    if (encoderDelta == 0) return;

    //for some cases we only want to know if value is increased or decreased (typically for menu items)
    if (encoderDelta>0) Serial.print("+");
    if (encoderDelta<0) Serial.print("-");

    //for other cases we want to know what is current value. Additionally often we only want if something changed
    //example: when using rotary encoder to set termostat temperature, or sound volume etc

    //if value is changed compared to our last read
    if (encoderDelta!=0) {
        //now we need current value
        int16_t encoderValue = rotaryEncoder.readEncoder();
        //process new value. Here is simple output.
        Serial.print("Value: ");
        Serial.println(encoderValue);

        s << "Value: " << encoderValue;
        Display.printAt_P(0,1,s.str().c_str());
    }

}

void rotaryenc_setup() {

    Display.clear();
    Display.printAt_P(0,0,"Rotary Encoder Test:");


    //we must initialize rorary encoder
    rotaryEncoder.begin();
    rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
    //optionally we can set boundaries and if values should cycle or not
    rotaryEncoder.setBoundaries(0, 10, true); //minValue, maxValue, cycle values (when max go to min and vice versa)
}

void rotaryenc_loop() {
    //in loop call your custom function which will process rotary encoder values
    rotary_loop();

    delay(50);
    if (millis()>20000) rotaryEncoder.enable ();
}
#endif
