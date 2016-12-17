#include "../include/dialog.h"
#include "../include/usefullFn.h"

GtkWidget *server,*dbusername,*dbpassword;
GtkWidget *cin,*nom,*prenom,*dns,*cnss,*sexe,*email,*numerotel,*ville,*adresse,*pwd_u,*un;
GtkWidget *view;
GtkListStore  *store;
int id;

void menu(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    close_window(win,p);
    creer_home_admin(win);
}

void cliquer_configuration(GtkWidget *wid,gpointer p)
{
    config(wid,p);
}

void logout_ad(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    gtk_widget_hide(win);
    authentification(win);
}

void about_info(GtkWidget *win,gpointer p)
{
    app_info_dialog(p);
}
void menu_bar(GtkWidget *menubar,GtkWidget *win)
{

    GtkWidget *fileMenu,*settMenu,*aideMenu;
    GtkWidget *fileMi,*settings,*aide;
    GtkWidget *menuMI,*lougoutMI,*quitMi,*setdb,*apropos;
    GtkWidget *sep;
    GtkAccelGroup *accel_group = NULL;
    GtkWidget *image;

    fileMenu = gtk_menu_new();
    fileMi = gtk_menu_item_new_with_mnemonic("GRH");
    menuMI = gtk_image_menu_item_new_with_label("Menu");
    image = gtk_image_new_from_file("images/icon/home.png");
    gtk_image_menu_item_set_image(menuMI, image);
    g_signal_connect(menuMI, "activate",menu,win);
    lougoutMI = gtk_image_menu_item_new_with_label("Se déconnecter");
    image = gtk_image_new_from_file("images/icon/logout.png");
    gtk_image_menu_item_set_image(lougoutMI, image);
    g_signal_connect(lougoutMI, "activate",logout_ad,win);
    sep = gtk_separator_menu_item_new();
    quitMi = gtk_image_menu_item_new_with_label("Quitter");
    image = gtk_image_new_from_file("images/icon/cancel.png");
    gtk_image_menu_item_set_image(quitMi, image);
    g_signal_connect(quitMi, "activate",gtk_main_quit,NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuMI);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), lougoutMI);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);

    settMenu = gtk_menu_new();
    settings = gtk_menu_item_new_with_mnemonic("Paramètres");
    setdb = gtk_image_menu_item_new_with_label("Connexion BD");
    image = gtk_image_new_from_file("images/icon/database.png");
    gtk_image_menu_item_set_image(setdb, image);
    g_signal_connect(setdb, "activate",cliquer_configuration,NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(settings), settMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(settMenu), setdb);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), settings);

    aideMenu = gtk_menu_new();
    aide = gtk_menu_item_new_with_mnemonic("Aide");
    apropos = gtk_image_menu_item_new_with_label("À propos");
    image = gtk_image_new_from_file("images/icon/about.png");
    gtk_image_menu_item_set_image(apropos, image);
    g_signal_connect(apropos, "activate",about_info,win);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(aide), aideMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(aideMenu), apropos);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), aide);
}

toolbar_fn(GtkWidget *toolbar,GtkWidget *win)
{
    GtkWidget *sep;
    GtkToolItem *homeTb;
    GtkToolItem *exitTb;
    GtkWidget *image;

    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    homeTb = gtk_tool_button_new_from_stock(GTK_STOCK_HOME);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), homeTb,-1);
    g_signal_connect(G_OBJECT(homeTb), "clicked",G_CALLBACK(menu), win);
    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);
    g_signal_connect(G_OBJECT(exitTb), "clicked",G_CALLBACK(logout_ad), win);
}


void valid_adduser(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    employe emp;
    emp.cinn = gtk_entry_get_text(GTK_ENTRY(cin));
    emp.nom = gtk_entry_get_text(GTK_ENTRY(nom));
    emp.username = gtk_entry_get_text(GTK_ENTRY(un));
    emp.prenom = gtk_entry_get_text(GTK_ENTRY(prenom));
    emp.dns = gtk_entry_get_text(GTK_ENTRY(dns));
    emp.cnss = gtk_entry_get_text(GTK_ENTRY(cnss));
    if(gtk_combo_box_get_active(sexe)==0)
    {
        emp.sexe = "Homme";
    }
    else
    {
        emp.sexe = "Femme";
    }
    emp.email = gtk_entry_get_text(GTK_ENTRY(email));
    emp.numerotel = gtk_entry_get_text(GTK_ENTRY(numerotel));
    emp.ville = gtk_entry_get_text(GTK_ENTRY(ville));
    emp.adresse = gtk_entry_get_text(GTK_ENTRY(adresse));
    emp.pwd_u = gtk_entry_get_text(GTK_ENTRY(pwd_u));
    if((strcmp(emp.username,"")==0) || (strcmp(emp.pwd_u,"")==0) || (strcmp(emp.cinn,"")==0) || (strcmp(emp.nom,"")==0) || (strcmp(emp.prenom,"")==0) || (strcmp(emp.dns,"")==0) || (strcmp(emp.cnss,"")==0) || (strcmp(emp.email,"")==0) || (strcmp(emp.numerotel,"")==0) )
    {
        show_error_invalide(p,"\nIl' y a des champs vide !");
    }
    else
    {
        if(add_user_db(emp)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier les données");
        }
        else
        {
            close_window(win,p);
            store = gtk_list_store_new (NUM_COLS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
            show_users(store,iter);
            gtk_tree_view_set_model (GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));
        }
    }

}

void add_user (GtkWidget *win,gpointer *p)
{

    GtkWidget *info,*espace,*lcin,*lun,*lnom,*lprenom,*ldns,*lcnss,*lsexe,*lemail,*lnumerotel,*lville,*ladresse,*lpwd_u;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Ajouter employé");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Ajouter employé : </b>\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    lcin = gtk_label_new("Cin : ");
    cin =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lcin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lun = gtk_label_new("Nom d'utilisateur : ");
    un =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lun, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), un, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    lpwd_u = gtk_label_new("Mot de Passe : ");
    pwd_u =  gtk_entry_new ();
    gtk_box_pack_start (GTK_BOX (hbox), lpwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), pwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


    lnom = gtk_label_new("Nom : ");
    nom =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lnom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), nom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lprenom = gtk_label_new("Prenom : ");
    prenom =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lprenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), prenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    ldns = gtk_label_new("Date naissance : ");
    dns =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_placeholder_text (dns,"jj/mm/aaaa");
    gtk_box_pack_start (GTK_BOX (hbox), ldns, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), dns, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lcnss = gtk_label_new("CNSS : ");
    cnss =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lcnss, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cnss, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lsexe = gtk_label_new("Sexe : ");
    sexe = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sexe), "Homme");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sexe), "Femme");
    gtk_combo_box_set_active (GTK_COMBO_BOX (sexe), 0);

    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lsexe, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), sexe, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lemail = gtk_label_new("Email : ");
    email =  gtk_entry_new();
    gtk_entry_set_placeholder_text (email,"mail@mail.com");
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lemail, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), email, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lnumerotel = gtk_label_new("Numéro de téléphone : ");
    numerotel =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lnumerotel, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), numerotel, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lville = gtk_label_new("Ville : ");
    ville =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lville, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), ville, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    ladresse = gtk_label_new("Adresse : ");
    adresse =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), ladresse, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), adresse, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    ok = gtk_button_new_with_label ("Ajouter");
    g_signal_connect (ok, "clicked",valid_adduser, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void valid_addres(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;

    employe emp;
    emp.cinn = gtk_entry_get_text(GTK_ENTRY(cin));
    emp.nom = gtk_entry_get_text(GTK_ENTRY(nom));
    emp.username = gtk_entry_get_text(GTK_ENTRY(un));
    emp.prenom = gtk_entry_get_text(GTK_ENTRY(prenom));
    emp.email = gtk_entry_get_text(GTK_ENTRY(email));
    emp.role = "Responsable";
    emp.pwd_u = gtk_entry_get_text(GTK_ENTRY(pwd_u));
    if((strcmp(emp.cinn,"")==0) || (strcmp(emp.nom,"")==0) || (strcmp(emp.prenom,"")==0) || (strcmp(emp.email,"")==0) )
    {
        show_error_invalide(p,"\nIl' y a des champs vide !");
    }
    else
    {
        if(add_res_db(emp)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier les données");
        }
        else
        {
            close_window(win,p);
            store = gtk_list_store_new (NUM_COLS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
            show_users(store,iter);
            gtk_tree_view_set_model (GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));
        }
    }

}

void add_res(GtkWidget *win,gpointer *p)
{

    GtkWidget *espace,*info;
    GtkWidget *lcin,*lnom,*lprenom,*lemail,*lpwd_u,*lres,*lun;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Ajouter Responsable");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Ajouter Responsable : </b>\n\n");

    espace = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    lcin = gtk_label_new("Cin : ");
    cin =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lcin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lun = gtk_label_new("Nom d'utilisateur : ");
    un =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lun, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), un, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


    hbox = gtk_hbox_new (TRUE, 6);
    lpwd_u = gtk_label_new("Mot de Passe : ");
    pwd_u =  gtk_entry_new ();
    gtk_box_pack_start (GTK_BOX (hbox), lpwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), pwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


    lnom = gtk_label_new("Nom : ");
    nom =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lnom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), nom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lprenom = gtk_label_new("Prenom : ");
    prenom =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lprenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), prenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lemail = gtk_label_new("Email : ");
    email =  gtk_entry_new();
    gtk_entry_set_placeholder_text (email,"mail@mail.com");
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lemail, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), email, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    ok = gtk_button_new_with_label ("Ajouter");
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    g_signal_connect (ok, "clicked",valid_addres, win);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void valid_modres(GtkWidget *win,gpointer *p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    employe emp;
    emp.cinn = gtk_entry_get_text(GTK_ENTRY(cin));
    emp.nom = gtk_entry_get_text(GTK_ENTRY(nom));
    emp.username = gtk_entry_get_text(GTK_ENTRY(un));
    emp.prenom = gtk_entry_get_text(GTK_ENTRY(prenom));
    emp.email = gtk_entry_get_text(GTK_ENTRY(email));
    emp.pwd_u = gtk_entry_get_text(GTK_ENTRY(pwd_u));
    if((strcmp(emp.cinn,"")==0) || (strcmp(emp.nom,"")==0) || (strcmp(emp.prenom,"")==0) || (strcmp(emp.email,"")==0) )
    {
        show_error_invalide(p,"\nIl' y a des champs vide !");
    }
    else
    {
        if(update_responsable(emp,id)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier les données");
        }
        else
        {
            close_window(win,p);
            store = gtk_list_store_new (NUM_COLS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
            show_users(store,iter);
            gtk_tree_view_set_model (GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));
        }
    }
}

void modifier_res(GtkWidget *win,employe *emp)
{

    GtkWidget *espace,*info;
    GtkWidget *lcin,*lnom,*lprenom,*lemail,*lpwd_u,*lun;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    gchar gcin[100],gemail[100],gnom[100],gprenom[100],gun[100],gpwd_u[100];

    strcpy(gcin,emp->cinn);
    strcpy(gemail,emp->email);
    strcpy(gnom,emp->nom);
    strcpy(gprenom,emp->prenom);
    strcpy(gun,emp->username);
    strcpy(gpwd_u,emp->pwd_u);

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Modifier Information Responsable");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Modifier Responsable : </b>\n\n");

    espace = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    lcin = gtk_label_new("Cin : ");
    cin =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(cin,gcin);
    gtk_box_pack_start (GTK_BOX (hbox), lcin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lun = gtk_label_new("Nom d'utilisateur : ");
    un =  gtk_entry_new();
    gtk_entry_set_text(un,gun);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lun, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), un, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    lpwd_u = gtk_label_new("Mot de Passe : ");
    pwd_u =  gtk_entry_new ();
    gtk_entry_set_text(pwd_u,gpwd_u);
    gtk_box_pack_start (GTK_BOX (hbox), lpwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), pwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lnom = gtk_label_new("Nom : ");
    nom =  gtk_entry_new();
    gtk_entry_set_text(nom,gnom);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lnom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), nom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lprenom = gtk_label_new("Prenom : ");
    prenom =  gtk_entry_new();
    gtk_entry_set_text(prenom,gprenom);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lprenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), prenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lemail = gtk_label_new("Email : ");
    email =  gtk_entry_new();
    gtk_entry_set_text(email,gemail);
    gtk_entry_set_placeholder_text (email,"mail@mail.com");
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lemail, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), email, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);

    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);

    ok = gtk_button_new_with_label ("Modifier");
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    g_signal_connect (ok, "clicked",valid_modres, win);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void valid_modemp(GtkWidget *win,gpointer *p)
{

    GtkTreeIter iter;
    GtkTreeModel *model;
    employe emp;
    emp.cinn = gtk_entry_get_text(GTK_ENTRY(cin));
    emp.nom = gtk_entry_get_text(GTK_ENTRY(nom));
    emp.username = gtk_entry_get_text(GTK_ENTRY(un));
    emp.prenom = gtk_entry_get_text(GTK_ENTRY(prenom));
    emp.dns = gtk_entry_get_text(GTK_ENTRY(dns));
    emp.cnss = gtk_entry_get_text(GTK_ENTRY(cnss));
    if(gtk_combo_box_get_active(sexe)==0)
    {
        emp.sexe = "Homme";
    }
    else
    {
        emp.sexe = "Femme";
    }
    emp.email = gtk_entry_get_text(GTK_ENTRY(email));
    emp.numerotel = gtk_entry_get_text(GTK_ENTRY(numerotel));
    emp.ville = gtk_entry_get_text(GTK_ENTRY(ville));
    emp.adresse = gtk_entry_get_text(GTK_ENTRY(adresse));
    emp.pwd_u = gtk_entry_get_text(GTK_ENTRY(pwd_u));
    if((strcmp(emp.cinn,"")==0) || (strcmp(emp.nom,"")==0) || (strcmp(emp.prenom,"")==0) || (strcmp(emp.dns,"")==0) || (strcmp(emp.cnss,"")==0) || (strcmp(emp.email,"")==0) || (strcmp(emp.numerotel,"")==0) )
    {
        show_error_invalide(p,"\nIl' y a des champs vide !");
    }
    else
    {
        if(update_emp(emp,id)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier les données");
        }
        else
        {
            close_window(win,p);
            store = gtk_list_store_new (NUM_COLS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
            show_users(store,iter);
            gtk_tree_view_set_model (GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));
        }
    }

}

void modifier_emp(GtkWidget *win,employe *emp)
{
    GtkWidget *info,*espace,*lcin,*lun,*lnom,*lprenom,*ldns,*lcnss,*lsexe,*lemail,*lnumerotel,*lville,*ladresse,*lpwd_u;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    gchar gcin[100],gemail[100],gnom[100],gprenom[100],gun[100],gpwd_u[100],gsexe[100],gdns[100],gvill[100],gadresse[100],gcnss[100],gnumtel[100];

    strcpy(gcin,emp->cinn);
    strcpy(gemail,emp->email);
    strcpy(gnom,emp->nom);
    strcpy(gprenom,emp->prenom);
    strcpy(gun,emp->username);
    strcpy(gsexe,emp->sexe);
    strcpy(gpwd_u,emp->pwd_u);
    strcpy(gdns,emp->dns);
    strcpy(gvill,emp->ville);
    strcpy(gadresse,emp->adresse);
    strcpy(gnumtel,emp->numerotel);
    strcpy(gcnss,emp->cnss);

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Modifier Information employé");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Modifier Information: </b>\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    lcin = gtk_label_new("Cin : ");
    cin =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(cin,gcin);
    gtk_box_pack_start (GTK_BOX (hbox), lcin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cin, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lun = gtk_label_new("Nom d'utilisateur : ");
    un =  gtk_entry_new();
    gtk_entry_set_text(un,gun);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lun, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), un, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    lpwd_u = gtk_label_new("Mot de Passe : ");
    pwd_u =  gtk_entry_new ();
    gtk_entry_set_text(pwd_u,gpwd_u);
    gtk_box_pack_start (GTK_BOX (hbox), lpwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), pwd_u, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


    lnom = gtk_label_new("Nom : ");
    nom =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(nom,gnom);
    gtk_box_pack_start (GTK_BOX (hbox), lnom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), nom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lprenom = gtk_label_new("Prenom : ");
    prenom =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(prenom,gprenom);
    gtk_box_pack_start (GTK_BOX (hbox), lprenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), prenom, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    ldns = gtk_label_new("Date naissance : ");
    dns =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_placeholder_text (dns,"jj/mm/aaaa");
    gtk_entry_set_text(dns,gdns);
    gtk_box_pack_start (GTK_BOX (hbox), ldns, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), dns, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lcnss = gtk_label_new("CNSS : ");
    cnss =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(cnss,gcnss);
    gtk_box_pack_start (GTK_BOX (hbox), lcnss, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cnss, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lsexe = gtk_label_new("Sexe : ");
    sexe = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sexe), "Homme");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sexe), "Femme");
    if(strcmp(gsexe,"Homme")==0)
    {
        gtk_combo_box_set_active (GTK_COMBO_BOX (sexe), 0);
    }
    else
    {
        gtk_combo_box_set_active (GTK_COMBO_BOX (sexe), 1);
    }


    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lsexe, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), sexe, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lemail = gtk_label_new("Email : ");
    email =  gtk_entry_new();
    gtk_entry_set_placeholder_text (email,"mail@mail.com");
    gtk_entry_set_text(email,gemail);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), lemail, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), email, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lnumerotel = gtk_label_new("Numéro de téléphone : ");
    numerotel =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(numerotel,gnumtel);
    gtk_box_pack_start (GTK_BOX (hbox), lnumerotel, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), numerotel, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    lville = gtk_label_new("Ville : ");
    ville =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(ville,gvill);
    gtk_box_pack_start (GTK_BOX (hbox), lville, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), ville, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    ladresse = gtk_label_new("Adresse : ");
    adresse =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_entry_set_text(adresse,gadresse);
    gtk_box_pack_start (GTK_BOX (hbox), ladresse, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), adresse, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);

    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);

    ok = gtk_button_new_with_label ("Modifier");
    g_signal_connect (ok, "clicked",valid_modemp, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);


    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


    gtk_widget_show_all (win);
}

void modifier (GtkWidget *win,gpointer *p)
{
    employe *emp = malloc (sizeof (employe));
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;
    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, COL_ID, &value,  -1);
    id = atoi(value);
    get_user(emp,id);
    if(strcmp(emp->role,"responsable")==0)
    {
        modifier_res(win,emp);
    }
    else if(strcmp(emp->role,"role_admin")==0)
    {
        show_error_invalide(p,"\nContacter Responsable Informatique\npour modifier information admin.");
    }
    else if(strcmp(emp->role,"Employe")==0)
    {
        modifier_emp(win,emp);
    }

}

void supp(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, COL_ROLE, &value,  -1);
    if(strcmp(value,"role_admin")==0)
    {
        show_error_invalide(p,"\nVous ne pouver pas supprimer un admin ! ");
    }
    else
    {
        gtk_tree_model_get(model, &iter, COL_ID, &value,  -1);
        delete_user(atoi(value));
    }
    g_free(value);
    store = gtk_list_store_new (NUM_COLS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    show_users(store,iter);
    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
}


void sauv_conf(GtkWidget *win,gpointer p)
{

    char *sr,*dbu,*dbpass;
    sr=gtk_entry_get_text(GTK_ENTRY(server));
    dbu=gtk_entry_get_text(GTK_ENTRY(dbusername));
    dbpass=gtk_entry_get_text(GTK_ENTRY(dbpassword));

    if((strcmp(sr,"")==0) || (strcmp(dbu,"")==0) || (strcmp(dbpass,"")==0))
    {
        show_error_invalide(p,"\nIl' y a des champs vide !");
    }
    else
    {
        sauv_conf_file(sr,dbu,dbpass);
        close_window(win,p);
    }
}

void config (GtkWidget *win,gpointer *p)
{
    char sr[20],dbu[20],dbpass[20];
    GtkWidget *lserver,*lusername,*lpassword,*info,*espace;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Configiration");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    get_conf_file(sr,dbu,dbpass);
    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Configuration Base de Donnée</b>\n\n");

    espace = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    lserver = gtk_label_new("Server : ");
    server =  gtk_entry_new();
    gtk_entry_set_placeholder_text (server,"localhost");
    gtk_entry_set_text(server,sr);
    gtk_box_pack_start (GTK_BOX (hbox), lserver, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), server, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    lusername = gtk_label_new("Username : ");
    dbusername =  gtk_entry_new();
    gtk_entry_set_placeholder_text (dbusername,"root");
    gtk_entry_set_text(dbusername,dbu);
    gtk_box_pack_start (GTK_BOX (hbox), lusername, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), dbusername, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    lpassword = gtk_label_new("Password : ");
    dbpassword =  gtk_entry_new ();
    gtk_entry_set_text(dbpassword,dbpass);
    gtk_box_pack_start (GTK_BOX (hbox), lpassword, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), dbpassword, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), espace, FALSE, FALSE, 0);
    hbox = gtk_hbox_new (TRUE, 6);
    ok = gtk_button_new_with_label ("Sauvgarder");
    g_signal_connect (ok, "clicked",G_CALLBACK (sauv_conf), win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void creer_home_admin(GtkWidget *win)
{
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL;
    GtkWidget *scrollbar = NULL;
    GtkWidget* text = NULL;
    GtkWidget *vbox1,*vbox;
    GtkWidget *hbox1 = NULL,*hbox2;
    GtkWidget *listBox = NULL;
    GtkWidget *buttonImage;
    GtkWidget *image = NULL;
    GtkWidget *user = NULL;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Espace Admin");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 500);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    hbox1 = gtk_hbox_new (FALSE, 0);
    vbox1 = gtk_vbox_new (FALSE, 0);
    hbox2 = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    view = gtk_tree_view_new();
    gtk_widget_set_size_request (view, 300,300);
    store = gtk_list_store_new (NUM_COLS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"ID",renderer,"text", COL_ID,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Nom",renderer,"text", COL_NOM,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Prenom",renderer,"text", COL_PRENOM, NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Role",renderer,"text", COL_ROLE,NULL);
    show_users(store,iter);
    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
    gtk_container_add (GTK_CONTAINER(scrollbar), view);
    gtk_widget_set_size_request (scrollbar, 300,300);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,50,25);

    user = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(user), "<b>Ajouter employé : </b>");
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/add_user.png");
    gtk_button_set_image(button,image);
    gtk_box_pack_start (GTK_BOX (vbox1), user, TRUE, TRUE, 10);
    gtk_box_pack_start (GTK_BOX (vbox1), button, TRUE, TRUE, 10);
    g_signal_connect (button, "clicked", add_user, view);

    user = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(user), "<b>Ajouter Responsable : </b>");
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/add_res.png");
    gtk_button_set_image(button,image);
    gtk_box_pack_start (GTK_BOX (vbox1), user, TRUE, TRUE, 10);
    gtk_box_pack_start (GTK_BOX (vbox1), button, TRUE, TRUE, 10);
    g_signal_connect (button, "clicked", add_res, win);

    gtk_fixed_put(GTK_FIXED(fixed),vbox1,420,10);

    button= gtk_button_new_with_label("Modifier");
    gtk_fixed_put(GTK_FIXED(fixed),button,190,350);
    g_signal_connect (button, "clicked", modifier, win);

    button= gtk_button_new_with_label("Supprimer");
    gtk_fixed_put(GTK_FIXED(fixed),button,270,350);
    g_signal_connect (button, "clicked", supp, win);

    gtk_widget_show_all (win);

}
