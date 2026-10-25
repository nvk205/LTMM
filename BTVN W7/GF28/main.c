#include "gf28.h"
#include <stdio.h>

typedef struct
{
    uint8_t a;
    uint8_t b;
    uint16_t mod;
}test_vecto;


int main(){

    test_vecto tests[6] = {
        {0x57, 0x83, 0x11B}, 
        {0x26, 0x9E, 0x11B}, 
        {0x80, 0x02, 0x11B}, 
        {0x53, 0xCA, 0x11B},  
        {0x57, 0x01, 0x11B},  
        {0x57, 0x00, 0x11B}   
    };

    printf("KET QUA\n\n");
    for (int i = 0; i < 6; i++) {
    uint8_t a = tests[i].a;
    uint8_t b = tests[i].b;
    uint16_t mod = tests[i].mod;

    uint8_t result = mul(a, b, mod);

    printf("Test %d: a = %2d (0x%X), b = %2d (0x%X), mod = %2d -> KET QUA = %2d (0x%X)\n", i + 1, a, a, b, b, mod, result, result);
    }

    return 0;
}