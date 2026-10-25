#include "gf24.h"
#include <stdio.h>

typedef struct
{
    uint8_t a;
    uint8_t b;
    uint8_t mod;
}test_vecto;


int main(){

    test_vecto tests[5] = {
        {10, 5,  19},  
        {2,  3,  19},  
        {8,  2,  19},  
        {5,  11, 19},  
        {15, 15, 19}
    };

    printf("KET QUA\n\n");
    for (int i = 0; i < 5; i++) {
    uint8_t a = tests[i].a;
    uint8_t b = tests[i].b;
    uint8_t mod = tests[i].mod;

    uint8_t result = mul(a, b, mod);

    printf("Test %d: a = %2d (0x%X), b = %2d (0x%X), mod = %2d -> KET QUA = %2d (0x%X)\n", i + 1, a, a, b, b, mod, result, result);
    }

    return 0;
}