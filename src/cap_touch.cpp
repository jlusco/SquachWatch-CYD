// SquachWatch-CYD - capacitive touch driver abstraction.
// LCDWiki ES3C28P: FocalTech FT6336G, I2C address 0x38.
// Existing RL Phantom path: CST816/CST820, I2C address 0x15.
#include "cap_touch.h"
#include <Arduino.h>
#include <Wire.h>

namespace CapTouch {

#if defined(LCDWIKI_ES3C28P)
static constexpr uint8_t ADDR = 0x38;
static constexpr uint8_t REG_STATUS = 0x02;
static constexpr uint8_t REG_TOUCH1 = 0x03;

static int sdaPin = -1;
static int sclPin = -1;
static int rstPin = -1;

static bool readBytes(uint8_t reg, uint8_t* data, size_t len) {
    Wire.beginTransmission(ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    size_t got = Wire.requestFrom((uint8_t)ADDR, (uint8_t)len);
    if (got != len) return false;
    for (size_t i = 0; i < len; ++i) data[i] = Wire.read();
    return true;
}

void begin(int sda, int scl, int rst) {
    sdaPin = sda;
    sclPin = scl;
    rstPin = rst;

    if (rstPin >= 0) {
        pinMode(rstPin, OUTPUT);
        digitalWrite(rstPin, HIGH);
        delay(20);
        digitalWrite(rstPin, LOW);
        delay(20);
        digitalWrite(rstPin, HIGH);
        delay(500); // Matches LCDWiki's supplied FT6336 driver.
    }

    Wire.begin(sdaPin, sclPin);
    Wire.setClock(400000);
}

bool probe() {
    Wire.beginTransmission(ADDR);
    return Wire.endTransmission() == 0;
}

bool read(uint16_t& x, uint16_t& y) {
    uint8_t status = 0;
    if (!readBytes(REG_STATUS, &status, 1)) return false;
    const uint8_t touches = status & 0x0F;
    if (touches == 0 || touches > 2) return false;

    uint8_t data[4] = {};
    if (!readBytes(REG_TOUCH1, data, sizeof(data))) return false;

    x = (uint16_t)(((data[0] & 0x0F) << 8) | data[1]);
    y = (uint16_t)(((data[2] & 0x0F) << 8) | data[3]);
    return true;
}

#else

// Existing CST816/CST820 implementation used by the RL Phantom capacitive path.
static const uint8_t ADDR = 0x15;

void begin(int sda, int scl, int rst) {
    pinMode(rst, OUTPUT);
    digitalWrite(rst, LOW);
    delay(10);
    digitalWrite(rst, HIGH);
    delay(50);
    Wire.begin(sda, scl);
}

bool probe() {
    Wire.beginTransmission(ADDR);
    return Wire.endTransmission() == 0;
}

bool read(uint16_t& x, uint16_t& y) {
    Wire.beginTransmission(ADDR);
    Wire.write(0x02);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom((uint8_t)ADDR, (uint8_t)5) != 5) return false;

    uint8_t fingerNum = Wire.read();
    uint8_t xh = Wire.read();
    uint8_t xl = Wire.read();
    uint8_t yh = Wire.read();
    uint8_t yl = Wire.read();
    if (fingerNum == 0) return false;

    x = ((uint16_t)(xh & 0x0F) << 8) | xl;
    y = ((uint16_t)(yh & 0x0F) << 8) | yl;
    return true;
}

#endif

} // namespace CapTouch
