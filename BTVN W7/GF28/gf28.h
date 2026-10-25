#ifndef GF28
#define GF28

#include <stdint.h>
// Cau hinh GF2^4
#define GF28_bit 8
#define GF28_FF 0x0FF
#define GF28_100 0x100

#define GF28_mod

uint8_t mul(uint8_t a, uint8_t b, uint16_t mod);

#endif