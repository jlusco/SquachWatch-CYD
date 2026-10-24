# LCDWiki ES3C28P integration

This build uses the LCDWiki-supplied TFT_eSPI 2.5.43 library as a local `lib/TFT_eSPI` library.

The SquachWatch raw-register FramePush optimization is intentionally disabled for this board. The ESP32-S3 LCDWiki sample uses TFT_eSPI's native `pushSprite()` path; using the SquachWatch raw-register path on the S3 can produce corrupted/garbled pixel transfers.

LCD:
- ILI9341V
- 240x320
- CS GPIO10
- DC GPIO46
- SCLK GPIO12
- MOSI GPIO11
- MISO GPIO13
- RESET tied to ESP32 reset (`TFT_RST=-1`)
- Backlight GPIO45, HIGH on
- SPI 40 MHz, matching LCDWiki

Touch:
- FT6336G I2C
- SDA GPIO16
- SCL GPIO15
- RESET GPIO18
- INT GPIO17
- Address 0x38
