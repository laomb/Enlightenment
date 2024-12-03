//
// Created by NotBonzo on 12/2/2024.
//

#ifndef EVENT_H
#define EVENT_H

#include <app/core.h>

#define APP_EVENT_TYPE_DELETE     1
#define APP_EVENT_TYPE_KEY_PRESS  2
#define APP_EVENT_TYPE_MOUSE_CLICK 3
#define APP_EVENT_TYPE_WINDOW_RESIZE 4

struct app_event {
    uint32_t type;
    union {
        struct {
            uint32_t key_code;
        } key_event;
        struct {
            uint32_t button;
            int32_t x;
            int32_t y;
        } mouse_event;
        struct {
            uint32_t width;
            uint32_t height;
        } resize_event;
    };
};

#endif //EVENT_H
