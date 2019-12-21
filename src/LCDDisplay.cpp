//
// Created by John Beeler on 12/19/19.
//

#include "LCDDisplay.h"
#include "IicLcd.h"

bool LCDDisplay::init() {
    // Initially, we're going to attempt to initialize an IIC display. If this succeeds (i.e. we find an I2C device)
    // then we'll use it
    has_iic_display = IICDisplay->init();
    if(has_iic_display) {
        clear();
        return true;
    }

    // Next, we're going to attempt a TFT display. Since we don't currently have a mechanism for detecting if a TFT
    // display is actually connected, this will always return true.
    has_tft_display = TFT_Display->init();
    if(has_tft_display) {
        clear();
        return true;
    }
    
    return false;
}

void LCDDisplay::clear() {
    if (has_iic_display)
        IICDisplay->clear();
    if (has_tft_display)
        TFT_Display->clear();
}


void LCDDisplay::printAt_P(uint8_t x, uint8_t y, const char* text){
    if (has_iic_display)
        IICDisplay->printAt_P(x, y, text);
    
    if (has_tft_display)  // x gets ignored here
        TFT_Display->printAt(y, 2, text);
}
