#include "des.h"

uint64_t IP_function(uint64_t plaintext)
{
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result <<= 1;
        result |= (plaintext >> (64 - IP[i])) & 1ULL;
    }
    return result;
}

uint64_t IP_inverse_function(uint64_t input)
{
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result <<= 1;
        result |= (input >> (64 - IP_INV[i])) & 1ULL;
    }
    return result;
}

uint32_t P_function(uint32_t input)
{
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1;
        result |= (input >> (32 - P[i])) & 1U;
    }
    return result;
}

uint64_t E_function(uint32_t input)
{
    uint64_t result = 0;
    for (int i = 0; i < 48; i++) {
        result <<= 1;
        result |= ((uint64_t)input >> (32 - E[i])) & 1ULL;
    }
    return result;
}

uint32_t f_function(uint32_t R, uint64_t ki)
{
    uint64_t expanded = E_function(R) ^ ki;
    uint32_t sbox_out = 0;

    for (int box = 0; box < 8; box++) {
        uint8_t six_bits = (uint8_t)((expanded >> (42 - 6 * box)) & 0x3F);
        int row = ((six_bits & 0x20) >> 4) | (six_bits & 0x01);
        int col = (six_bits >> 1) & 0x0F;
        sbox_out = (sbox_out << 4) | SBOX[box][row][col];
    }

    return P_function(sbox_out);
}

uint64_t PC1_function(uint64_t key)
{
    uint64_t result = 0;
    for (int i = 0; i < 56; i++) {
        result <<= 1;
        result |= (key >> (64 - PC1[i])) & 1ULL;
    }
    return result;
}

uint64_t PC2_function(uint64_t input)
{
    uint64_t result = 0;
    for (int i = 0; i < 48; i++) {
        result <<= 1;
        result |= (input >> (56 - PC2[i])) & 1ULL;
    }
    return result;
}

uint64_t left_shift(uint64_t input, int s)
{
    input &= 0x0FFFFFFFULL;
    return ((input << s) | (input >> (28 - s))) & 0x0FFFFFFFULL;
}

void gen_subkey(uint64_t key, uint64_t k[16])
{
    uint64_t V = PC1_function(key);
    uint64_t C = (V >> 28) & 0x0FFFFFFFULL;
    uint64_t D = V & 0x0FFFFFFFULL;

    for (int i = 0; i < 16; i++) {
        C = left_shift(C, SHIFTS[i]);
        D = left_shift(D, SHIFTS[i]);
        k[i] = PC2_function((C << 28) | D);
    }
}

uint64_t process_block(uint64_t input, uint64_t key, int is_decrypt)
{
    uint64_t k[16];
    gen_subkey(key, k);

    uint64_t block = IP_function(input);
    uint32_t L = (uint32_t)(block >> 32);
    uint32_t R = (uint32_t)block;

    for (int i = 0; i < 16; i++) {
        uint32_t oldR = R;
        uint64_t ki = k[is_decrypt ? (15 - i) : i];
        R = L ^ f_function(R, ki);
        L = oldR;
    }

    uint64_t pre_output = ((uint64_t)R << 32) | L;
    return IP_inverse_function(pre_output);
}

uint64_t des_encrypt(uint64_t plaintext, uint64_t key)
{
    return process_block(plaintext, key, 0);
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key)
{
    return process_block(ciphertext, key, 1);
}