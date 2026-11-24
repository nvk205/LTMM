#include "aes128.h"
#include "aes_tables.h"

static uint8_t gf_mul(uint8_t a, uint8_t b)
{
    uint8_t res = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            res ^= a;
        }
        uint8_t hi_bit = a & 0x80;
        a <<= 1;
        if (hi_bit) {
            a ^= 0x1b;
        }
        b >>= 1;
    }
    return res;
}

static void add_round_key(uint8_t state[4][4], const uint8_t round_key[16])
{
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            state[r][c] ^= round_key[c * 4 + r];
        }
    }
}

static void sub_bytes(uint8_t state[4][4])
{
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = SBOX[state[r][c]];
        }
    }
}

static void inv_sub_bytes(uint8_t state[4][4])
{
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = INV_SBOX[state[r][c]];
        }
    }
}

static void shift_rows(uint8_t state[4][4])
{
    uint8_t tmp;

    tmp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = tmp;

    tmp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = tmp;
    tmp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = tmp;

    tmp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = tmp;
}

static void inv_shift_rows(uint8_t state[4][4])
{
    uint8_t tmp;

    tmp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = tmp;

    tmp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = tmp;
    tmp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = tmp;

    tmp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = tmp;
}

static void mix_columns(uint8_t state[4][4])
{
    uint8_t col[4];
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            col[r] = state[r][c];
        }
        state[0][c] = gf_mul(col[0], 2) ^ gf_mul(col[1], 3) ^ col[2] ^ col[3];
        state[1][c] = col[0] ^ gf_mul(col[1], 2) ^ gf_mul(col[2], 3) ^ col[3];
        state[2][c] = col[0] ^ col[1] ^ gf_mul(col[2], 2) ^ gf_mul(col[3], 3);
        state[3][c] = gf_mul(col[0], 3) ^ col[1] ^ col[2] ^ gf_mul(col[3], 2);
    }
}

static void inv_mix_columns(uint8_t state[4][4])
{
    uint8_t col[4];
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            col[r] = state[r][c];
        }
        state[0][c] = gf_mul(col[0], 14) ^ gf_mul(col[1], 11) ^ gf_mul(col[2], 13) ^ gf_mul(col[3], 9);
        state[1][c] = gf_mul(col[0], 9)  ^ gf_mul(col[1], 14) ^ gf_mul(col[2], 11) ^ gf_mul(col[3], 13);
        state[2][c] = gf_mul(col[0], 13) ^ gf_mul(col[1], 9)  ^ gf_mul(col[2], 14) ^ gf_mul(col[3], 11);
        state[3][c] = gf_mul(col[0], 11) ^ gf_mul(col[1], 13) ^ gf_mul(col[2], 9)  ^ gf_mul(col[3], 14);
    }
}

void aes128_encrypt(const uint8_t plaintext[AES_BLOCK_SIZE],
                    uint8_t ciphertext[AES_BLOCK_SIZE],
                    const uint8_t round_keys[AES_ROUNDS + 1][AES_BLOCK_SIZE])
{
    uint8_t state[4][4];

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = plaintext[c * 4 + r];
        }
    }

    add_round_key(state, round_keys[0]);

    for (int round = 1; round < AES_ROUNDS; round++) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, round_keys[round]);
    }

    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, round_keys[AES_ROUNDS]);

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            ciphertext[c * 4 + r] = state[r][c];
        }
    }
}

void aes128_decrypt(const uint8_t ciphertext[AES_BLOCK_SIZE],
                    uint8_t plaintext[AES_BLOCK_SIZE],
                    const uint8_t round_keys[AES_ROUNDS + 1][AES_BLOCK_SIZE])
{
    uint8_t state[4][4];

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = ciphertext[c * 4 + r];
        }
    }

    add_round_key(state, round_keys[AES_ROUNDS]);

    for (int round = AES_ROUNDS - 1; round >= 1; round--) {
        inv_shift_rows(state);
        inv_sub_bytes(state);
        add_round_key(state, round_keys[round]);
        inv_mix_columns(state);
    }

    inv_shift_rows(state);
    inv_sub_bytes(state);
    add_round_key(state, round_keys[0]);

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            plaintext[c * 4 + r] = state[r][c];
        }
    }
}