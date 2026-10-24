// SquachWatch-CYD — TFT_eSPI setup for the LCDWiki 2.8-inch ESP32-S3 Display
// (ES3C28P capacitive-touch / ES3N28P touchless variants).
//
// LCDWiki's published pin table matches the Freenove S3 2.8-inch display for
// the LCD and FT6336 touch controller: ILI9341V, 240x320, LCD SPI on GPIO
// 11/12/13, CS 10, DC 46, backlight 45; touch I2C SDA 16 / SCL 15 and reset
// GPIO18. The panel reset is shared with ESP32-S3 reset. See:
// https://www.lcdwiki.com/2.8inch_ESP32-S3_Display
//
// LCDWiki-specific configuration. Do not define FREENOVE_S3 in the LCDWiki
// environment: that macro selects Freenove-specific runtime inversion and
// peripheral behavior in the application. The LCDWiki SD slot is SDIO and
// remains disabled until a dedicated SDIO driver is added.
#pragma once

#define USER_SETUP_INFO    "SquachWatch-CYD / LCDWiki ESP32-S3 2.8 inch / ILI9341"

#define ILI9341_DRIVER
#define TFT_WIDTH   240
#define TFT_HEIGHT  320

#define TFT_MISO  13
#define TFT_MOSI  11
#define TFT_SCLK  12
#define TFT_CS    10
#define TFT_DC    46
#define TFT_RST   -1
#define TFT_BL    45
#define TFT_BACKLIGHT_ON HIGH

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define SMOOTH_FONT

// Conservative initial clock for LCDWiki panels. High SPI clocks can cause
// speckled pixels, horizontal noise, or unstable rows on some ILI9341V panels.
// Increase only after confirming stable output on the actual board.
#ifndef SPI_FREQUENCY
#define SPI_FREQUENCY         40000000
#endif
#define SPI_READ_FREQUENCY    20000000

#define TFT_INVERSION_OFF
#define TFT_RGB_ORDER TFT_RGB
