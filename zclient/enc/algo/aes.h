//
// Created by NotBonzo on 12/3/2024.
//
/**
 * @file aes.h
 * @brief AES (Advanced Encryption Standard) API for encryption and decryption.
 *
 * This header provides an interface for using AES in various modes
 * (ECB, CBC, CTR) for encryption and decryption of data blocks.
 *
 * Modes like CBC require an initialization vector (IV) while ECB operates
 * on fixed-size blocks without additional input. Key sizes of 128, 192,
 * and 256 bits are supported.
 *
 * Notes:
 * - Ensure the input length is a multiple of AES_BLOCK_SIZE (16 bytes).
 * - For dynamic memory handling, the caller must ensure proper cleanup
 *   for keys and IVs unless otherwise noted. AES Context is cleaned up and initialised by callie
 */
#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <app/core.h>

#define AES_BLOCK_SIZE 16   ///< AES block size in bytes
#define AES_MAX_KEY_SIZE 32 ///< Maximum AES key size in bytes (256-bit)

/**
 * @brief Enum specifying AES operation modes.
 */
typedef uint8_t aes_mode;
enum {
    AES_MODE_ECB = 0x1,     ///< Electronic Codebook Mode
    AES_MODE_CBC,           ///< Cipher Block Chaining Mode
    AES_MODE_CTR            ///< Counter Mode
};

/**
 * @brief Represents an AES encryption or decryption context.
 * @element key: Pointer to the encryption/decryption key.
 * @element key_state: The dynamic memory state of the key.
 * @element key_length: Length of the key in bytes (16, 24, 32 for AES-128, AES-192, AES-256)
 * @element mode: AES mode of operation (ECB, CBC, CTR, etc.).
 * @element iv: Pointer to the initialization vector (IV) for modes requiring it
 *              Must be null for ECB mode.
 * @element iv_state: The dynamic memory state of the IV.
 */
struct aes_context {
    const uint8_t* key;
    app_dynamic_memory_state key_state;
    uint32_t key_length;
    aes_mode mode;
    const uint8_t* iv;
    app_dynamic_memory_state iv_state;
};

/**
 * @brief Initializes an AES context.
 * @param ctx: Pointer to the AES context pointer to initialize.
 * @param key: Pointer to the encryption key.
 * @param key_length: Length of the encryption key in bytes (16, 24, or 32).
 * @param mode: AES mode of operation.
 * @param iv: Pointer to the initialization vector (IV), can be NULL for modes not requiring it.
 * @returns:
 *      * 0 if the context was successfully initialized.
 *      * -1 if the provided parameters are invalid.
 */
int aes_init(struct aes_context** ctx, const uint8_t* key, uint32_t key_length, enum aes_mode mode, const uint8_t* iv);

/**
 * @brief Encrypts a block of data using AES.
 * @param ctx: Pointer to an initialized AES context.
 * @param input: Pointer to the input data block to encrypt.
 * @param output: Pointer to a buffer to store the encrypted output. Must be at least as large as input.
 * @param length: Length of the input data in bytes. Must be a multiple of 16.
 * @returns:
 *      * 0 if encryption was successful.
 *      * -1 if the input parameters are invalid.
 */
int aes_encrypt(const struct aes_context* ctx, const uint8_t* input, uint8_t* output, uint32_t length);


/**
 * @brief Decrypts a block of data using AES.
 * @param ctx: Pointer to an initialized AES context.
 * @param input: Pointer to the input data block to decrypt.
 * @param output: Pointer to a buffer to store the decrypted output. Must be at least as large as input.
 * @param length: Length of the input data in bytes. Must be a multiple of 16.
 * @returns:
 *      * 0 if decryption was successful.
 *      * -1 if the input parameters are invalid.
 */
int aes_decrypt(const struct aes_context* ctx, const uint8_t* input, uint8_t* output, uint32_t length);

/**
 * @brief Cleans up resources associated with an AES context.
 * @param ctx: Pointer to the AES context to clean up.
 */
void aes_cleanup(struct aes_context* ctx);

#endif //AES_H
