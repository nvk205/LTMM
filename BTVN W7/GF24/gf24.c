#include "gf24.h"
#include <stdio.h>


uint8_t mul(uint8_t a, uint8_t b, uint8_t mod){
    a &= GF24_F;
    b &= GF24_F;

    uint8_t result = 0;

    for (int i = 0; i < GF24_bit; i++)
    {
        //xet bit cuoi b = 1 thi result + a
        if ((b & 0x01) == 1)
        {
            result ^= a;
        }
        // a * x tuong duong dich trai 1 bit
        a <<= 1;

        //5 bit thi ha bac a xor m
        if ((a & GF24_10) == GF24_10){
            a ^= mod;
        }

        //xet bit tiep theo
        b >>= 1;
        
    }
    
    return result & GF24_F;
}


