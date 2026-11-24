#include <stdio.h>
#include "des.h"

int main(void)
{
    /* Vi du chuan trong giao trinh DES */
    uint64_t plaintext = 0x0123456789ABCDEFULL;
    uint64_t key       = 0x133457799BBCDFF1ULL;

    uint64_t ciphertext = des_encrypt(plaintext, key);
    uint64_t decrypted  = des_decrypt(ciphertext, key);

    printf("Ban ro  : %016llX\n", (unsigned long long)plaintext);
    printf("Khoa K  : %016llX\n", (unsigned long long)key);
    printf("Ban ma  : %016llX\n", (unsigned long long)ciphertext);
    printf("Giai ma : %016llX\n", (unsigned long long)decrypted);

    return 0;
}