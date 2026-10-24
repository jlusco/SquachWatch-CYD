// LCDWiki 2.8" ESP32-S3 ES3C28P / ES3N28P V1.0
// Hardware setup copied from the manufacturer's supplied TFT_eSPI User_Setup.h.
#pragma once

#define USER_SETUP_INFO "LCDWiki ES3C28P / ILI9341V"
#define LCDWIKI_ES3C28P 1
#define ILI9341_DRIVER

#define TFT_BL 45
#define TFT_BACKLIGHT_ON HIGH

#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10
#define TFT_DC   46
#define TFT_RST  -1

// LCDWiki manufacturer configuration: 40 MHz display SPI.
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 20000000

#define LOAD_GLCD
#define LOAD_FONT2

// Do NOT force TFT_RGB_ORDER or TFT_INVERSION here. The manufacturer's
// ILI9341 init sequence establishes the panel's expected MADCTL state,
// and SquachWatch applies its own rotation/color-order handling.
