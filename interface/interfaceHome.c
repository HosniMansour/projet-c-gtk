#include <gtk/gtk.h>
#include "../include/interfaceConnection.h"
#include "../include/interfaceAdmin.h"
#include "../include/interfaceEmploye.h"
#include "../include/interfaceResponsable.h"

void creer_home(int x)
{
    GtkWidget *win = NULL;
    if(x==1)
    {
        creer_home_admin(win);
    }
    else if(x==2)
    {
        creer_home_emp(win);
    }
    else if(x==3)
    {
        creer_home_res(win);
    }
}
