//
// Created by NotBonzo on 12/2/2024.
//
#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <app/core.h>
#include <app/event.h>

enum {
    APP_WINDOW_FLAGS_MAXIMIZED = 0x1,
    APP_WINDOW_FLAGS_MINIMIZED = 0x2,
    APP_WINDOW_FLAGS_FULLSCREEN = 0x4,
};

/**
 * @brief Main app window event handler, called user triggered event occurs
 * @param event: struct describing the occurred event, given by reference
 * @returns:
 *      * 0 if successfully handled event
 *      * -1 if a recoverable error has been handled gracefully
 *      * -2 if an unrecoverable error has occurred and the internal event handler should propagate it terminating the
 * application
 */
typedef int8_t(*app_window_event_callback)(struct app_event* event);

/**
 * Base window class that all platform specific window structs will compose of
 * @element width: Specifies the width of the window. Is updated on user resize
 * @element height: Specifies the height of the window. Is updated on user resize
 *
 * @element x: The current horizontal position of the window on screen. 0 if in state that doesn't support floating windows. Is updated on user resize
 * @element y: The current vertical position of the window on screen. 0 if in state that doesn't support floating windows. Is updated on user resize
 *
 * @element event_callback: Pointers to the callback handler, more info available at its definition
 * @element title: Pointer to the first element of a string holding the current name
 *
 * @element title_state: Dynamic memory state describing how memory can be operated on
 *
 * @element flags: Bitmask specifying the attributes of the window as specified in the anonymous enum APP_WINDOW_FLAGS_*
**/
struct app_window {
    uint32_t width, height;                             // 64 bits
    int32_t x, y;                                       // 64 bits
    app_window_event_callback event_callback;           // 64 bits
    char* title;                                        // 64 bits
    app_dynamic_memory_state title_state;               // 8 bits
    uint8_t flags;                                      // 8 bits
};

/**
 * @brief Initializes a new app window.
 * @param width: Initial width of the window.
 * @param height: Initial height of the window.
 * @param title: Initial title for the window (can be nullptr).
 * @param flags: Initial flags for the window.
 * @returns A pointer to the newly created window, or nullptr on failure.
 */
struct app_window* app_window_create(uint32_t width, uint32_t height, const char* title, uint8_t flags);

/**
 * @brief Frees resources associated with an app window.
 * @param window: Pointer to the window to destroy. Safe to call with nullptr.
 */
void app_window_destroy(struct app_window* window);

#endif //WINDOW_H
