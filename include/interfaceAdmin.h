#ifndef INTERFACEADMIN_H_INCLUDED
#define INTERFACEADMIN_H_INCLUDED
#include "../include/TypeDef.h"
#include "../interface/interfaceAdmin.c"

void cliquer_btn_gerer_cmpts(GtkWidget *wid,gpointer p);
void cliquer_configuration(GtkWidget *wid,gpointer p);
void creer_home_admin(GtkWidget *win);
void menu(GtkWidget *win,gpointer p);
void creer_fenetre_gerer_comptes(GtkWidget *win,gpointer* p);
void valid_adduser(GtkWidget *win,gpointer p);
void add_user (GtkWidget *win,gpointer *p);
void valid_addres(GtkWidget *win,gpointer p);
void add_res(GtkWidget *win,gpointer *p);
void valid_modres(GtkWidget *win,gpointer *p);
void modifier_res(GtkWidget *win,employe *emp);
void valid_modemp(GtkWidget *win,gpointer *p);
void modifier_emp(GtkWidget *win,employe *emp);
void modifier (GtkWidget *win,gpointer *p);
void supp(GtkWidget *win,gpointer p);
void creer_fenetre_gerer_comptes (GtkWidget *win,gpointer *p);
void sauv_conf(GtkWidget *win,gpointer p);
void config (GtkWidget *win,gpointer *p);

#endif // INTERFACEADMIN_H_INCLUDED
