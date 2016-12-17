#include <stdlib.h>
#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
    GtkWidget *win = NULL;
    gtk_init (&argc, &argv);
    authentification(win);
    gtk_main();
    return 0;
}
