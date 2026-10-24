# TFT_eSPI, ESP32-C5 support

TFT_eSPI 2.5.43 is the newest release upstream has made (March 2024) and it has
never heard of the ESP32-C5. Asked to build for one it falls through to the
plain-Xtensa processor and dies on `VSPI_HOST` and `SPI_MOSI_DLEN_REG`.

The two `.c/.h` files here are RockBase IoT's C5 processor port, taken from
their board-support repository at the same TFT_eSPI version they were written
against:

  https://github.com/RockBase-iot/NM-CYD-C5
  Demos/Arduino/libraries/TFT_eSPI/Processors/

`extra_script.py` installs them into the TFT_eSPI that PlatformIO downloads,
and adds the two `#elif defined(CONFIG_IDF_TARGET_ESP32C5)` lines that reach
them, for the `nm-cyd-c5` environment only. Nothing is copied or patched for
any other board.

Why not vendor the whole library under `lib/`? Two reasons. A library in
`lib/` outranks the registry copy for EVERY environment, so it would silently
swap the display driver under all ten Xtensa boards. And the full tree is
35 MB across 600 files of fonts and examples to gain four lines and two files.

If upstream TFT_eSPI ever ships C5 support, delete this directory and the
`patch_tft_espi_for_c5` block in `extra_script.py`; the guard there already
no-ops when the C5 branch is present.


### LCDWiki 2.8-inch ESP32-S3 display troubleshooting update

The `lcdwiki-s3` environment now uses TFT_eSPI standard `ILI9341_DRIVER`, does not force the HSPI port, and starts with RGB order and inversion off. It also no longer defines `FREENOVE_S3`, which activates Freenove-specific runtime behavior. These settings are a diagnostic configuration to test against the LCDWiki ES3C28P/ES3N28P; they have not been validated on physical hardware. Build with `pio run -e lcdwiki-s3 -t upload`. If this still produces a white/garbled display, flash LCDWiki's own demo as a hardware baseline before further changes.
