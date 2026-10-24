# LCDWiki ES3C28P integration

This version adds the LCDWiki 2.8-inch ESP32-S3 ES3C28P as a first-class PlatformIO target.

## Hardware mapping

| Function | GPIO |
|---|---:|
| ILI9341 CS | 10 |
| ILI9341 DC | 46 |
| ILI9341 SCLK | 12 |
| ILI9341 MOSI | 11 |
| ILI9341 MISO | 13 |
| LCD reset | EN (shared hardware reset) |
| Backlight | 45 |
| FT6336G SDA | 16 |
| FT6336G SCL | 15 |
| FT6336G reset | 18 |
| FT6336G interrupt | 17 |
| FT6336G I2C address | 0x38 |

## PlatformIO

Use `lcdwiki-es3c28p`.

The target is configured for ESP32-S3 N16R8: 16 MB QIO flash and 8 MB OPI PSRAM. It retains SquachWatch's two-slot OTA partition table.

## Touch

The existing `CapTouch` abstraction uses the FT6336G register map when `LCDWIKI_ES3` is defined. Touch is read in the panel's native 240x320 coordinate system and then passed through SquachWatch's existing affine calibration/rotation system.

## Backlight

GPIO45 is assigned its own LEDC channel. Existing CYD backlight channels remain unchanged for the other targets.

## Not changed

The LCDWiki single-wire RGB LED on GPIO42 is deliberately not wired into the existing three-channel status-light driver because that driver assumes three independent common-anode PWM pins. The display, capacitive touch, backlight, Wi-Fi/BLE, SD, and the rest of SquachWatch remain available.
