#include <stdio.h>
#include "aes128.h"

void in_hex(const char *ten, const uint8_t data[AES_BLOCK_SIZE])
{
    printf("%-16s: ", ten);
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
