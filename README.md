# BrewPi-ESP Build Test Firmware

This firmware tests that a complete BrewPi-ESP build is working correctly. This firmware specifically tests the:

- OneWire temperature sensors (connected & not in parasitic mode)
- "Heat" and "Cool" relays
- IIC LCD Screen (if present)
- TFT Screen (if present, ESP32 only)

This firmware also:

- Disconnects any previously connected WiFi network
- Initializes the filesystem

Pinouts tested by this firmware match those used for my BrewPi-ESP PCBs available in the [thorrak_hardware repo](https://github.com/thorrak/thorrak_hardware) and on my [Tindie store](https://www.tindie.com/stores/thorrak/). Support is available for the following controller types:


## ESP8266

ESP8266 support targets the [Lolin D1 Mini](https://www.wemos.cc/en/latest/d1/d1_mini.html).

### Expected Pinout

- **heatingPin** - D0 / 16
- **coolingPin** - D5 / 14
- **oneWirePin** - D6 / 12
- **doorPin** - D7 / 13
- **IIC_SDA** - D2 / 4
- **IIC_SCL** - D1 / 5

The D1 Mini was originally a NodeMCU board, and - depending on when the board was manufactured - may either have NodeMCU style pin numbering (e.g. D0, D5) or ESP8266-style pin numbering (e.g. 16, 14). The placement/physical pins are the same - only the silkscreen/labeling is different.

**NOTE** - There are issues with the Lolin D1 Mini v4.0.0 when flashing SPIFFS/LittleFS partitions. It is recommended to use the earlier revision of the board ([v3.1.0](https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html)) if possible.


## ESP32

ESP32 support targets the [Lolin D32](https://www.wemos.cc/en/latest/d32/d32.html) and [D32 Pro](https://www.wemos.cc/en/latest/d32/d32_pro.html). The BrewPi-ESP firmware supports both IIC and TFT screens, as well as hardware such as Bluetooth temperature sensors and Kasa WiFi switches that are not physically connected. Only physically connected hardware will be tested.

### Expected Pinout

- **heatingPin** - 25
- **coolingPin** - 26
- **oneWirePin** - 13
- **doorPin** - 34
- **IIC_SDA** - 21
- **IIC_SCL** - 22
- **TFT_CS** - 14 *(Matches D32 Pro LCD connector)*
- **TFT_DC** - 27 *(Matches D32 Pro LCD connector)*
- **TFT_RST** - 33 *(Matches D32 Pro LCD connector)*
- **TS_CS** - 12 *(Matches D32 Pro LCD connector)*
- **TFT_BACKLIGHT** - 32 *(Matches D32 Pro LCD connector)*

**NOTE** - The same firmware is used to test both IIC and TFT screens. If both an IIC and TFT screen are connected, only the IIC screen will be initialized/tested.


## ESP32-S2

ESP32-S2 support targets the [Lolin S2 Mini](https://www.wemos.cc/en/latest/s2/s2_mini.html). The Lolin S2 mini has a physical footprint that is compatible with the Lolin D1 mini, and the pins below were selected such that their physical placement will match the physical placement of the corresponding pins for a D1-based build. 

### Expected Pinout

- **heatingPin** - 5
- **coolingPin** - 7
- **oneWirePin** - 9
- **doorPin** - 11
- **IIC_SDA** - 33
- **IIC_SCL** - 35

**NOTE** - The ESP32-S2 has a built in USB controller which can lead to issues when flashing - especially when flashing a board for the first time. If you encounter difficulty when flashing, do the following:

1. Plug the Lolin S2 Mini into your computer
2. Hold down the "0" button on the right of the board
3. While continuing to hold the "0" button, press the "RST" button on the left of the board
4. Wait several seconds, then release the "0" button
5. Flash your controller with the desired firmware
6. Manually press the "RST" button on the left of the board to reset the controller once flashing is complete
