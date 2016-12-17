#include <string.h>

void jour_month_year(GtkWidget * jour,GtkWidget *month,GtkWidget *year)
{
    int i;
    char ch[5];
    for (i=1; i<=31; i++)
    {
        sprintf(ch, "%d", i);
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (jour), ch);
    }
    gtk_combo_box_set_active (GTK_COMBO_BOX (jour), 0);
    for (i=1; i<=12; i++)
    {
        sprintf(ch, "%d", i);
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (month), ch);
    }
    gtk_combo_box_set_active (GTK_COMBO_BOX (month), 0);
    for (i=2016; i<=2020; i++)
    {
        sprintf(ch, "%d", i);
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (year), ch);
    }
    gtk_combo_box_set_active (GTK_COMBO_BOX (year), 0);

}


void get_conf_file(char sr[],char dbu[],char dbpass[])
{
    FILE *fichier;
    fichier = fopen("data/db.txt", "r");
    fscanf(fichier, "%s %s %s", sr, dbu, dbpass);
    fclose(fichier);
}

void generatecv()
{
    int id=Getsession();

    employe *emp = malloc (sizeof (employe));
    get_user(emp,id);

    char cmd[100];

    sprintf(cmd,"rm -r /tmp/cv%d",id);
    system(cmd);

    sprintf(cmd,"cp -r cv /tmp/cv%d",id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<nom>/%s/g' /tmp/cv%d/index.html",emp->nom,id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<prenom>/%s/g' /tmp/cv%d/index.html",emp->prenom,id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<tel>/%s/g' /tmp/cv%d/index.html",emp->numerotel,id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<adr>/%s/g' /tmp/cv%d/index.html",emp->adresse,id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<vil>/%s/g' /tmp/cv%d/index.html",emp->ville,id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<mail>/%s/g' /tmp/cv%d/index.html",emp->email,id);
    system(cmd);

    sprintf(cmd,"sed -i 's/<expp>/%s/g' /tmp/cv%d/index.html",emp->expe,id);
    system(cmd);

    /*sprintf(cmd,"sed -i 's/<ln>/%s/g' /tmp/cv%d/index.html",emp->lnnnn,id);
    system(cmd);*/

    show_compitance_id_valid(id);
    show_diplome_id_valid(id);

    sprintf(cmd,"wkhtmltopdf /tmp/cv%d/index.html /tmp/cv.pdf ",id);
    system(cmd);

    system("evince /tmp/cv.pdf");
}

void sendmail(char to[],char nom[],char username[],char passwrd[])
{
    char cmd[100];
    char tempFile[100];
    strcpy(tempFile,tempnam("/tmp","sendmail"));
    FILE *fp = fopen(tempFile,"w");
    fprintf(fp,"Bonjour %s,\n\nVotre compte votre compte a été créé.\n\nNom d'utilisateur : %s \nMot de Passe : %s \n \n merci.",nom,username,passwrd);
    fclose(fp);
    sprintf(cmd,"mail -s 'GRH : Nouveau compte' %s < %s",to,tempFile);
    system(cmd);
}


void logout(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    gtk_widget_hide(win);
    authentification(win);
}

void close_window(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
}

void sauv_conf_file(char *sr,char *dbu,char *dbpass)
{
    FILE *fichier;
    fichier = fopen("data/db.txt", "w");
    fprintf(fichier, "%s %s %s", sr,dbu,dbpass);
    fclose(fichier);
}

void addsession(int id)
{
    FILE *fichier;
    fichier = fopen("data/session.txt", "w");
    fprintf(fichier, "%d", id);
    fclose(fichier);
}

int Getsession()
{
    int id;
    FILE *fichier;
    fichier = fopen("data/session.txt", "r");
    fscanf(fichier, "%d", &id);
    fclose(fichier);
    return id;
}
