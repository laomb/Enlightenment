#include <app/window.h>
#include <gtk/gtk.h>

int main()
{
    struct app_window* window = app_window_create(600, 800, "Hello World", 0);

    gtk_main();

    app_window_destroy(window);
    return 0;
}
