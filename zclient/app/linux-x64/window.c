//
// Created by NotBonzo on 12/2/2024.
//
#include <app/window.h>
#include <assert.h>
#include <stdlib.h>
#include <gtk/gtk.h>

struct platform_app_window {
    struct app_window base;
    GtkWidget* window;
};

static int8_t platform_app_default_callback_handler(struct app_event*) {
    return 0;
}

static gboolean platform_app_event_handler(GdkEvent* event, const gconstpointer data) {
    const struct platform_app_window* app_window = (struct platform_app_window*)data;
    struct app_event app_evt = {0};

    switch (event->type) {
        case GDK_DELETE:
            app_evt.type = APP_EVENT_TYPE_DELETE;
            break;
        case GDK_KEY_PRESS: {
            app_evt.type = APP_EVENT_TYPE_KEY_PRESS;
            app_evt.key_event.key_code = ((GdkEventKey*)event)->keyval;
            break;
        }
        case GDK_BUTTON_PRESS: {
            app_evt.type = APP_EVENT_TYPE_MOUSE_CLICK;
            const GdkEventButton * button_event = (GdkEventButton*)event;
            app_evt.mouse_event.button = button_event->button;
            app_evt.mouse_event.x = (int32_t)button_event->x;
            app_evt.mouse_event.y = (int32_t)button_event->y;
            break;
        }
        case GDK_CONFIGURE: {
            app_evt.type = APP_EVENT_TYPE_WINDOW_RESIZE;
            const GdkEventConfigure * configure_event = (GdkEventConfigure*)event;
            app_evt.resize_event.width = configure_event->width;
            app_evt.resize_event.height = configure_event->height;
            break;
        }
        default:
            return FALSE;
    }

    if (app_window->base.event_callback) {
        return app_window->base.event_callback(&app_evt);
    }

    return FALSE;
}

struct app_window* app_window_create(const uint32_t width, const uint32_t height, const char* title,
                                     const uint8_t flags) {
    struct platform_app_window* app_window = calloc(1, sizeof(struct platform_app_window));
    assert(app_window != nullptr);

    app_window->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    app_window->base.width = width;
    app_window->base.height = height;

    if (title != nullptr) {
        app_window->base.title = strdup(title);
        app_window->base.title_state = APP_DYNAMIC_MEMORY_HEAP;
        gtk_window_set_title(GTK_WINDOW(app_window->window), app_window->base.title);
    }

    app_window->base.flags = flags;

    if ((flags & APP_WINDOW_FLAGS_MAXIMIZED) == APP_WINDOW_FLAGS_MAXIMIZED) {
        gtk_window_maximize(GTK_WINDOW(app_window->window));
    } else if ((flags & APP_WINDOW_FLAGS_MINIMIZED) == APP_WINDOW_FLAGS_MINIMIZED) {
        gtk_window_iconify(GTK_WINDOW(app_window->window));
    } else if ((flags & APP_WINDOW_FLAGS_FULLSCREEN) == APP_WINDOW_FLAGS_FULLSCREEN) {
        gtk_window_fullscreen(GTK_WINDOW(app_window->window));
    }

    gtk_window_set_default_size(GTK_WINDOW(app_window->window), width, height);
    gtk_window_set_position(GTK_WINDOW(app_window->window), GTK_WIN_POS_CENTER);

    if ((flags & APP_WINDOW_FLAGS_MAXIMIZED) == APP_WINDOW_FLAGS_MAXIMIZED ||
        (flags & APP_WINDOW_FLAGS_FULLSCREEN) == APP_WINDOW_FLAGS_FULLSCREEN) {
        app_window->base.x = app_window->base.y = 0;
    } else {
        gtk_window_get_position(GTK_WINDOW(app_window->window), &app_window->base.x, &app_window->base.y);
    }

    app_window->base.event_callback = platform_app_default_callback_handler;

    g_signal_connect(app_window->window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
    g_signal_connect(app_window->window, "delete-event", G_CALLBACK(platform_app_event_handler), app_window);
    g_signal_connect(app_window->window, "key-press-event", G_CALLBACK(platform_app_event_handler), app_window);
    g_signal_connect(app_window->window, "button-press-event", G_CALLBACK(platform_app_event_handler), app_window);
    g_signal_connect(app_window->window, "configure-event", G_CALLBACK(platform_app_event_handler), app_window);

    gtk_widget_show_all(app_window->window);

    return &app_window->base;
}

void app_window_destroy(struct app_window* window) {
    struct platform_app_window* app_window = (struct platform_app_window*)window;

    if (app_window != nullptr) {
        if (app_window->window != nullptr) {
            gtk_widget_destroy(app_window->window);
        }

        if (app_window->base.title != nullptr && app_window->base.title_state == APP_DYNAMIC_MEMORY_HEAP) {
            free(app_window->base.title);
        }

        free(app_window);
    }
}