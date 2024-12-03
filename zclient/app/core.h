//
// Created by NotBonzo on 12/2/2024.
//

#ifndef CORE_H
#define CORE_H

typedef void* app_psd_ptr; // App platform specific data pointer

typedef uint8_t app_dynamic_memory_state;
enum {
    APP_DYNAMIC_MEMORY_FREED = 0,           // Memory is already freed or not yet allocated
    APP_DYNAMIC_MEMORY_HEAP,                // Memory is on app controlled heap, may be freed when destructing object
    APP_DYNAMIC_MEMORY_EXTERN,              // Memory is on an externally managed place, only given a pointer, should not be freed
};

#endif //CORE_H
