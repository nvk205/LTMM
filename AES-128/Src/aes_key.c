#include "aes128.h"
#include "aes_tables.h"

static void rot_word(uint8_t word[4])
{
    uint8_t tmp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = tmp;
}

static void sub_word(uint8_t word[4])
{
    for (int i = 0; i < 4; i++) {
        word[i] = SBOX[word[i]];
    }
}

void aes128_key_expansion(const uint8_t key[AES_KEY_SIZE],
                          uint8_t round_keys[AES_ROUNDS + 1][AES_BLOCK_SIZE])
{
    uint8_t temp[4];

    for (int i = 0; i < AES_KEY_SIZE; i++) {
        round_keys[0][i] = key[i];
    }

    for (int round = 1; round <= AES_ROUNDS; round++) {
        for (int i = 0; i < 4; i++) {
            temp[i] = round_keys[round - 1][12 + i];
        }

        rot_word(temp);
        sub_word(temp);
        temp[0] ^= RCON[round];

        for (int i = 0; i < 4; i++) {
            round_keys[round][i] = round_keys[round - 1][i] ^ temp[i];
        }

        for (int i = 4; i < 16; i++) {
            round_keys[round][i] = round_keys[round - 1][i] ^ round_keys[round][i - 4];
        }
    }
}