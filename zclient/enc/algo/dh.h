//
// Created by NotBonzo on 12/3/2024.
//
/**
 * @file dh.h
 * @brief Diffie-Hellman (DH) Key Exchange API for secure key agreement.
 *
 * This header provides an interface for performing Diffie-Hellman key exchange
 * operations to securely derive shared secrets between two parties.
 *
 * Supports custom prime modulus (p) and base (g) values for flexibility.
 *
 * Notes:
 * - Ensure the chosen prime (p) and generator (g) satisfy the security requirements.
 * - Both parties must agree on the same p and g values before performing the exchange.
 */
#ifndef DH_H
#define DH_H

#include <app/core.h>
#include <stdint.h>

/**
 * @brief Represents a Diffie-Hellman key exchange context.
 * @element prime: Pointer to the prime number used in the DH exchange.
 * @element prime_state: The dynamic memory state of the prime number.
 * @element generator: Pointer to the generator used in the DH exchange.
 * @element generator_state: The dynamic memory state of the generator.
 * @element private_key: Pointer to the private key (randomly generated).
 * @element private_key_state: The dynamic memory state of the private key.
 * @element public_key: Pointer to the public key (computed from the private key).
 * @element public_key_state: The dynamic memory state of the public key.
 * @element shared_key: Pointer to the shared secret key (computed after key exchange).
 * @element shared_key_state: The dynamic memory state of the shared key.
 */
struct dh_context {
    const uint8_t* prime;
    app_dynamic_memory_state prime_state;
    const uint8_t* generator;
    app_dynamic_memory_state generator_state;
    uint8_t* private_key;
    app_dynamic_memory_state private_key_state;
    uint8_t* public_key;
    app_dynamic_memory_state public_key_state;
    uint8_t* shared_key;
    app_dynamic_memory_state shared_key_state;
};

/**
 * @brief Initializes a Diffie-Hellman context with specified parameters.
 * @param ctx: Pointer to the DH context pointer to initialize.
 * @param prime: Pointer to the prime number.
 * @param prime_length: Length of the prime number in bytes.
 * @param generator: Pointer to the generator.
 * @param generator_length: Length of the generator in bytes.
 * @returns:
 *      * 0 if the context was successfully initialized.
 *      * -1 if the provided parameters are invalid.
 */
int dh_init(struct dh_context** ctx, const uint8_t* prime, uint32_t prime_length, const uint8_t* generator, uint32_t generator_length);

/**
 * @brief Generates a Diffie-Hellman private and public key pair.
 * @param ctx: Pointer to an initialized DH context.
 * @returns:
 *      * 0 if the keys were successfully generated.
 *      * -1 if the context is invalid or key generation fails.
 */
int dh_generate_key_pair(struct dh_context* ctx);

/**
 * @brief Computes the shared secret key using the other party's public key.
 * @param ctx: Pointer to an initialized DH context.
 * @param other_public_key: Pointer to the other party's public key.
 * @param other_public_key_length: Length of the other party's public key in bytes.
 * @returns:
 *      * 0 if the shared key was successfully computed.
 *      * -1 if the input parameters are invalid.
 */
int dh_compute_shared_key(struct dh_context* ctx, const uint8_t* other_public_key, uint32_t other_public_key_length);

/**
 * @brief Retrieves the public key from the DH context.
 * @param ctx: Pointer to an initialized DH context.
 * @param public_key: Pointer to a buffer to store the public key.
 * @param public_key_length: Pointer to the length of the buffer. Updated with the actual length of the public key.
 * @returns:
 *      * 0 if the public key was successfully retrieved.
 *      * -1 if the context is invalid or buffer is insufficient.
 */
int dh_get_public_key(const struct dh_context* ctx, uint8_t* public_key, uint32_t* public_key_length);

/**
 * @brief Retrieves the shared secret key from the DH context.
 * @param ctx: Pointer to an initialized DH context.
 * @param shared_key: Pointer to a buffer to store the shared key.
 * @param shared_key_length: Pointer to the length of the buffer. Updated with the actual length of the shared key.
 * @returns:
 *      * 0 if the shared key was successfully retrieved.
 *      * -1 if the context is invalid or buffer is insufficient.
 */
int dh_get_shared_key(const struct dh_context* ctx, uint8_t* shared_key, uint32_t* shared_key_length);

/**
 * @brief Cleans up resources associated with a Diffie-Hellman context.
 * @param ctx: Pointer to the DH context to clean up.
 */
void dh_cleanup(struct dh_context* ctx);

#endif // DH_H
