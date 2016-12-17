#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED
#include "../functions/Utilisateur.c"

int verifierLoginPwd(char * login, char * pwd,int *id);
int add_user_db(employe emp);
void ajouterItemUtilisateur (GtkWidget *listbox, char *sText);
void show_users(GtkListStore  *store,GtkTreeIter iter);
void get_user(employe *e,int id);

#endif // UTILISATEUR_H_INCLUDED
