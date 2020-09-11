#include "Rand.h"

uint32_t func_xor(void) {
    static uint32_t y = 2463534242;

    y = y ^ (y << 13);
    y = y ^ (y >> 17);

    return y = y ^ (y << 5);
}