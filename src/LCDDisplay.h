//
// Created by John Beeler on 12/19/19.
//

#ifndef BREWPI_ESP8266_BUILD_TEST_LCDDISPLAY_H
#define BREWPI_ESP8266_BUILD_TEST_LCDDISPLAY_H

#include "IicLcd.h"
#include "DisplayTFT.h"


class LCDDisplay {
public:
    bool init();

    void clear();

    void printAt_P(uint8_t x, uint8_t y, const char* text);
    //void print(const char* text);

    bool has_iic_display;
    bool has_tft_display;

//private:
    IIClcd *IICDisplay;
    TFTDisplay *TFT_Display;

};


#endif //BREWPI_ESP8266_BUILD_TEST_LCDDISPLAY_H
