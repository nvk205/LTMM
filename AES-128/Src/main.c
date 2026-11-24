#include <stdio.h>
#include <string.h>
#include "aes128.h"

static void chay_test(const char *tieu_de,
                      const uint8_t key[16],
                      const uint8_t plain[16],
                      const uint8_t cipher_mau[16])
{
    uint8_t round_keys[11][16];
    uint8_t cipher[16];
    uint8_t giai_ma[16];

    printf("%s\n", tieu_de);

    in_hex("Ban ro", plain);
    in_hex("Khoa K", key);

    aes128_key_expansion(key, round_keys);

    aes128_encrypt(plain, cipher, round_keys);
    printf("\n");
    in_hex("Ban ma tinh duoc", cipher);
    in_hex("Ban ma mau", cipher_mau);

    aes128_decrypt(cipher, giai_ma, round_keys);
    printf("\n");
    in_hex("Ban ro giai ma", giai_ma);

}

int main(void)
{


    /*  Vi du (FIPS-197 Appendix C.1) */
    const uint8_t key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };
    const uint8_t plain[16] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };
    const uint8_t cipher[16] = {
        0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
        0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a
    };

    chay_test("TEST ", key, plain, cipher);

    return 0;
}