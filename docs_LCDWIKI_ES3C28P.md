# SquachWatch-CYD - LCDWiki ES3C28P integration

Target: LCDWiki 2.8-inch ESP32-S3 ES3C28P (ILI9341V + FT6336G).

## Hardware mapping

- LCD CS: GPIO10
- LCD DC/RS: GPIO46
- LCD SCLK: GPIO12
- LCD MOSI: GPIO11
- LCD MISO: GPIO13
- LCD RESET: ESP32-S3 EN/reset line (no separate GPIO)
- LCD backlight: GPIO45, HIGH = ON
- Touch SDA: GPIO16
- Touch SCL: GPIO15
- Touch RESET: GPIO18
- Touch INT: GPIO17 (not required by SquachWatch polling path)

These assignments are from LCDWiki's supplied Arduino package and product documentation.

## Display driver

`lib/LCDWiki_TFT_eSPI` is LCDWiki's supplied TFT_eSPI 2.5.43 package. It is used by the `lcdwiki-es3c28p` PlatformIO environment, so the existing SquachWatch environments retain their normal library configuration.

The board-specific setup is `include/lcdwiki_es3c28p_user_setup.h`.

## Touch driver

`src/cap_touch.cpp` uses the LCDWiki FT6336G register map at I2C address `0x38` for this environment. The existing CST816/CST820 implementation remains available for the other capacitive board.

## Build

```text
pio run -e lcdwiki-es3c28p
pio run -e lcdwiki-es3c28p -t upload
```

The environment uses `esp32-s3-devkitc-1` with 16 MB flash and OPI PSRAM settings. `esp32s3` is not a PlatformIO board ID.
