//
// Created by NotBonzo on 12/3/2024.
//
/**
 * @file rsa.h
 * @brief RSA (Rivest–Shamir–Adleman) API for encryption, decryption, signing, and verification.
 *
 * This header provides an interface for using RSA for cryptographic operations,
 * including encryption, decryption, digital signing, and signature verification.
 *
 * Supports variable key sizes (e.g., 1024, 2048, 4096 bits) depending on the application.
 *
 * Notes:
 * - Ensure proper padding (e.g., PKCS#1 v1.5 or OAEP) is used for secure operations.
 * - RSA requires large integers; use appropriate use.
 */
#ifndef RSA_H
#define RSA_H

#include <app/core.h>
#include <stdint.h>

/**
 * @brief Enum specifying RSA padding schemes.
 */
typedef uint8_t rsa_padding;
enum {
    RSA_PADDING_NONE = 0x1, ///< No padding (not recommended for secure operations)
    RSA_PADDING_PKCS1,      ///< PKCS#1 v1.5 padding
    RSA_PADDING_OAEP,       ///< Optimal Asymmetric Encryption Padding (OAEP)
    RSA_PADDING_PSS         ///< Probabilistic Signature Scheme (PSS) for signing
};

/**
 * @brief Represents an RSA key.
 * @element modulus: Pointer to the modulus (n) of the RSA key.
 * @element modulus_state: The dynamic memory state of the modulus.
 * @element modulus_length: Length of the modulus in bytes.
 * @element exponent: Pointer to the exponent (e or d) of the RSA key.
 * @element exponent_state: The dynamic memory state of the exponent.
 * @element exponent_length: Length of the exponent in bytes.
 */
struct rsa_key {
    const uint8_t* modulus;
    app_dynamic_memory_state modulus_state;
    uint32_t modulus_length;
    const uint8_t* exponent;
    app_dynamic_memory_state exponent_state;
    uint32_t exponent_length;
};

/**
 * @brief Initializes an RSA key structure.
 * @param key: Pointer to the RSA key structure to initialize.
 * @param modulus: Pointer to the modulus (n).
 * @param modulus_length: Length of the modulus in bytes.
 * @param exponent: Pointer to the exponent (e or d).
 * @param exponent_length: Length of the exponent in bytes.
 * @returns:
 *      * 0 if the key was successfully initialized.
 *      * -1 if the provided parameters are invalid.
 */
int rsa_key_init(struct rsa_key** key, const uint8_t* modulus, uint32_t modulus_length, const uint8_t* exponent, uint32_t exponent_length);

/**
 * @brief Encrypts data using RSA.
 * @param key: Pointer to the RSA public key.
 * @param input: Pointer to the input data to encrypt.
 * @param input_length: Length of the input data in bytes.
 * @param output: Pointer to a buffer to store the encrypted output.
 * @param output_length: Pointer to the length of the output buffer. Updated with the actual length of the encrypted data.
 * @param padding: Padding scheme to use (e.g., RSA_PADDING_PKCS1 or RSA_PADDING_OAEP).
 * @returns:
 *      * 0 if encryption was successful.
 *      * -1 if the input parameters are invalid.
 */
int rsa_encrypt(const struct rsa_key* key, const uint8_t* input, uint32_t input_length, uint8_t* output, uint32_t* output_length, rsa_padding padding);

/**
 * @brief Decrypts data using RSA.
 * @param key: Pointer to the RSA private key.
 * @param input: Pointer to the input data to decrypt.
 * @param input_length: Length of the input data in bytes.
 * @param output: Pointer to a buffer to store the decrypted output.
 * @param output_length: Pointer to the length of the output buffer. Updated with the actual length of the decrypted data.
 * @param padding: Padding scheme to use (e.g., RSA_PADDING_PKCS1 or RSA_PADDING_OAEP).
 * @returns:
 *      * 0 if decryption was successful.
 *      * -1 if the input parameters are invalid.
 */
int rsa_decrypt(const struct rsa_key* key, const uint8_t* input, uint32_t input_length, uint8_t* output, uint32_t* output_length, rsa_padding padding);

/**
 * @brief Signs a message using RSA.
 * @param key: Pointer to the RSA private key.
 * @param input: Pointer to the input message to sign.
 * @param input_length: Length of the input message in bytes.
 * @param output: Pointer to a buffer to store the signature.
 * @param output_length: Pointer to the length of the output buffer. Updated with the actual length of the signature.
 * @param padding: Padding scheme to use (e.g., RSA_PADDING_PSS).
 * @returns:
 *      * 0 if signing was successful.
 *      * -1 if the input parameters are invalid.
 */
int rsa_sign(const struct rsa_key* key, const uint8_t* input, uint32_t input_length, uint8_t* output, uint32_t* output_length, rsa_padding padding);

/**
 * @brief Verifies a message signature using RSA.
 * @param key: Pointer to the RSA public key.
 * @param input: Pointer to the original message.
 * @param input_length: Length of the original message in bytes.
 * @param signature: Pointer to the signature to verify.
 * @param signature_length: Length of the signature in bytes.
 * @param padding: Padding scheme to use (e.g., RSA_PADDING_PSS).
 * @returns:
 *      * 0 if the signature is valid.
 *      * -1 if the signature is invalid or the input parameters are incorrect.
 */
int rsa_verify(const struct rsa_key* key, const uint8_t* input, uint32_t input_length, const uint8_t* signature, uint32_t signature_length, rsa_padding padding);

/**
 * @brief Cleans up resources associated with an RSA key.
 * @param key: Pointer to the RSA key to clean up.
 */
void rsa_key_cleanup(struct rsa_key* key);

#endif // RSA_H
