#ifndef AES128_H
#define AES128_H

#include <stdint.h>

#define AES_BLOCK_SIZE 16
#define AES_KEY_SIZE   16
#define AES_ROUNDS     10

void aes128_key_expansion(const uint8_t key[AES_KEY_SIZE],
                          uint8_t round_keys[AES_ROUNDS + 1][AES_BLOCK_SIZE]);

void aes128_encrypt(const uint8_t plaintext[AES_BLOCK_SIZE],
                    uint8_t ciphertext[AES_BLOCK_SIZE],
                    const uint8_t round_keys[AES_ROUNDS + 1][AES_BLOCK_SIZE]);

void aes128_decrypt(const uint8_t ciphertext[AES_BLOCK_SIZE],
                    uint8_t plaintext[AES_BLOCK_SIZE],
                    const uint8_t round_keys[AES_ROUNDS + 1][AES_BLOCK_SIZE]);

void in_hex(const char *ten, const uint8_t data[AES_BLOCK_SIZE]);

#endif