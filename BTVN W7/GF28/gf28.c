#include "gf28.h"
#include <stdio.h>


uint8_t mul(uint8_t a, uint8_t b, uint16_t mod){
    uint16_t temp_a = a & GF28_FF;
    b &= GF28_FF;

    uint8_t result = 0;

    for (int i = 0; i < GF28_bit; i++)
    {
        //xet bit cuoi b = 1 thi result + a
        if ((b & 0x01) == 1)
        {
            result ^= (uint8_t)(temp_a & GF28_FF);
        }
        // a * x tuong duong dich trai 1 bit
        temp_a <<= 1;

        //5 bit thi ha bac a xor m
        if ((temp_a & GF28_100) == GF28_100){
            temp_a ^= mod;
        }

        //xet bit tiep theo
        b >>= 1;
        
    }
    
    return result & GF28_FF;
}


