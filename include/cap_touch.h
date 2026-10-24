// SquachWatch-CYD - capacitive touch abstraction.
// Supports the LCDWiki ES3C28P FT6336G as well as the existing CST816/CST820 board.
#pragma once
#include <stdint.h>

namespace CapTouch {
    void begin(int sda, int scl, int rst);
    bool probe();
    bool read(uint16_t& x, uint16_t& y);
}
