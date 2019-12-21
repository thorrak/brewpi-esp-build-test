//
// Created by John Beeler on 11/28/19.
//

#ifndef LEGACY_PLATFORMIO_DISPLAYTFT_H
#define LEGACY_PLATFORMIO_DISPLAYTFT_H

// Pin definitions for TFT displays
#define TFT_CS 14  //for D32 Pro
#define TFT_DC 27  //for D32 Pro
#define TFT_RST 33 //for D32 Pro
#define TS_CS  12 //for D32 Pro
#define TFT_BACKLIGHT 32


class TFTDisplay //DISPLAY_SUPERCLASS
{
public:
    // initializes the lcd display
    bool init();

    void clear();
    void clearForText(uint8_t start_x, uint8_t start_y, uint16_t color, uint8_t font_size, uint8_t characters);
    void printAt(uint8_t y, uint8_t font_size, const char* text);

};


#endif //LEGACY_PLATFORMIO_DISPLAYTFT_H
