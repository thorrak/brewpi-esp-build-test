/*
 * Copyright 2019 John Beeler.
 *
 * This file has been added to BrewPi by the author noted above. It should be assumed to be available under the same
 * license terms as BrewPi, unless separate arrangements have been made with the author.
 *
 */

#include <limits.h>
#include <stdint.h>
#include <string>


#include "DisplayTFT.h"

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//#include <XPT2046_Touchscreen.h>



Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


bool toggleBacklight;


#ifndef min
#define min _min
#endif

#ifndef max
#define max _max
#endif



bool TFTDisplay::init(void){
    toggleBacklight = false;

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

#if defined(TFT_BACKLIGHT)
    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH);
#endif

    // TODO - Figure out how to test if a TFT actually gets initialized here, and adjust the return value accordingly
    return true;
}

#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif


//void TFTDisplay::printEEPROMStartup(void){
//
//    toggleBacklight = false;  // Assuming we need this
//
//    clear();
//
//    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
//    tft.setTextSize(WIFI_FONT_SIZE);
//
//    tft.setCursor(0, 0);
//
//    tft.println("Setting up EEPROM...");
//    tft.println("Please wait. This");
//    tft.println("can take 5+ minutes");
//    tft.println("for new installs.");
//    tft.println("");
//
//    tft.print("AP Name: ");
//    tft.println(WIFI_SETUP_AP_NAME);
//
//    tft.print("AP Pass: ");
//    tft.println(WIFI_SETUP_AP_PASS);
//
//}

void TFTDisplay::clear(void) {
    tft.fillScreen(ILI9341_BLACK);
}

void TFTDisplay::clearForText(uint8_t start_x, uint8_t start_y, uint16_t color, uint8_t font_size, uint8_t characters) {
    uint8_t width = (font_size * characters * 5) + (font_size * (characters-1) * 4);
    uint8_t height = font_size * 9;

    tft.fillRect(start_x, start_y, width, height, color);
}

void TFTDisplay::printAt(uint8_t row_num, uint8_t font_size, const char* text) {

    uint8_t x = 0;
    uint8_t y = font_size * 9 * row_num;

    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(font_size);
    //clearForText(x, y, ILI9341_BLACK, font_size, 4);

    tft.setCursor(x,y);
    tft.print(text);
}





