#include "gf24.h"
#include <stdio.h>

int main(){
    uint8_t a = 10;
    uint8_t b = 5;
    uint8_t mod = 19;
    uint8_t result = mul(a, b, mod);
    printf("%d", result);
}