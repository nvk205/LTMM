#ifndef GF24
#define GF24

#include <stdint.h>
// Cau hinh GF2^4
#define GF24_bit 4
#define GF24_F 0x0F
#define GF24_10 0x10

#define GF24_mod

uint8_t mul(uint8_t a, uint8_t b, uint8_t mod);

#endif