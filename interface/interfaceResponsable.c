GtkWidget *server,*dbusername,*dbpassword,*salaire;
GtkWidget *cin,*nom,*prenom,*dns,*cnss,*sexe,*email,*numerotel,*ville,*adresse,*pwd_u,*un;
GtkWidget *view,*licempview,*conview,*view1,*view2;
GtkListStore  *store,*text_view2;
GtkListStore  *storeC,*storeD;
int id;


/**************************** Menu / Logout / About *********************************/

void menu_r(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    gtk_widget_hide(win);
    creer_home_res(win);
}

void logout_r(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    gtk_widget_hide(win);
    authentification(win);
}

void about_info_r(GtkWidget *win,gpointer p)
{
    app_info_dialog(p);
}

void menu_bar_r(GtkWidget *menubar,GtkWidget *win)
{
    GtkWidget *fileMenu,*aideMenu;
    GtkWidget *fileMi,*aide;
    GtkWidget *menuMI,*lougoutMI,*quitMi,*apropos;
    GtkWidget *sep;
    GtkAccelGroup *accel_group = NULL;
    GtkWidget *image;

    fileMenu = gtk_menu_new();
    fileMi = gtk_menu_item_new_with_mnemonic("GRH");
    menuMI = gtk_image_menu_item_new_with_label("Menu");
    image = gtk_image_new_from_file("images/icon/home.png");
    gtk_image_menu_item_set_image(menuMI, image);
    g_signal_connect(menuMI, "activate",menu_r,win);
    lougoutMI = gtk_image_menu_item_new_with_label("Se déconnecter");
    image = gtk_image_new_from_file("images/icon/logout.png");
    gtk_image_menu_item_set_image(lougoutMI, image);
    g_signal_connect(lougoutMI, "activate",logout_r,win);
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

    aideMenu = gtk_menu_new();
    aide = gtk_menu_item_new_with_mnemonic("Aide");
    apropos = gtk_image_menu_item_new_with_label("À propos");
    image = gtk_image_new_from_file("images/icon/about.png");
    gtk_image_menu_item_set_image(apropos, image);
    g_signal_connect(apropos, "activate",about_info_r,win);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(aide), aideMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(aideMenu), apropos);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), aide);
}

void toolbar_fn_r(GtkWidget *toolbar,GtkWidget *win)
{
    GtkWidget *sep;
    GtkToolItem *homeTb;
    GtkToolItem *exitTb;
    GtkWidget *image;

    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    homeTb = gtk_tool_button_new_from_stock(GTK_STOCK_HOME);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), homeTb,-1);
    g_signal_connect(G_OBJECT(homeTb), "clicked",G_CALLBACK(menu_r), win);
    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);
    g_signal_connect(G_OBJECT(exitTb), "clicked",G_CALLBACK(logout_r), win);
}

/****************************** Gérer Utilisateur *********************************************/

void valid_adduser_r(GtkWidget *win,gpointer p)
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

void add_user_r (GtkWidget *win,gpointer *p)
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
    g_signal_connect (ok, "clicked",valid_adduser_r, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", gtk_widget_hide, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void valid_modemp_r(GtkWidget *win,gpointer *p)
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

void modifier_emp_r(GtkWidget *win,employe *emp)
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
    g_signal_connect (ok, "clicked",valid_modemp_r, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);


    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


    gtk_widget_show_all (win);
}

void modifier_r (GtkWidget *win,gpointer *p)
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
    if(strcmp(emp->role,"Responsable")==0)
    {
        show_error_invalide(p,"\nvou ne pouvez pas modifier information Responsable.");
    }
    else if(strcmp(emp->role,"role_admin")==0)
    {
        show_error_invalide(p,"\nContacter Responsable Informatique\npour modifier information admin.");
    }
    else if(strcmp(emp->role,"Employe")==0)
    {
        modifier_emp_r(win,emp);
    }
}


void supp_r(GtkWidget *win,gpointer p)
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
    else if(strcmp(value,"Responsable")==0)
    {
        show_error_invalide(p,"\nVous ne pouver pas supprimer un responsable ! ");
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


void gerer_empl(GtkWidget *win,gpointer p)
{

    gtk_widget_hide(p);
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL;
    GtkWidget* text = NULL;
    GtkWidget *vbox1,*vbox;
    GtkWidget *hbox1 = NULL,*hbox2;
    GtkWidget *listBox = NULL;
    GtkWidget *buttonImage;
    GtkWidget *image = NULL;
    GtkWidget *user = NULL;
    GtkWidget *scrollbar = NULL;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Espace Responsable");
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
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
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
    g_signal_connect (button, "clicked", add_user_r, view);

    gtk_fixed_put(GTK_FIXED(fixed),vbox1,420,10);

    button= gtk_button_new_with_label("Modifier");
    gtk_fixed_put(GTK_FIXED(fixed),button,190,350);
    g_signal_connect (button, "clicked", modifier_r, win);

    button= gtk_button_new_with_label("Supprimer");
    gtk_fixed_put(GTK_FIXED(fixed),button,270,350);
    g_signal_connect (button, "clicked", supp_r, win);

    gtk_widget_show_all (win);

}


/******************************** chercher *****************************************************/

void show_recherche(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *ss = gtk_entry_get_text(GTK_ENTRY(text_view2) );
    store = gtk_list_store_new (5,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING);
    searsh_skill_db(store,iter,ss);
    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
}

void chercher_emp(GtkWidget *win,gpointer p)
{

    gtk_widget_hide(p);
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL;
    GtkWidget *scrollbar = NULL;
    GtkWidget *info = NULL;
    GtkWidget *vbox;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Chercher Employés");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 490);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Chercher Employé par mot clé : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,50);

    text_view2 = gtk_entry_new();
    gtk_widget_set_size_request (text_view2, 450, 30);
    gtk_fixed_put(GTK_FIXED(fixed),text_view2,35,100);

    button= gtk_button_new_with_label("Chercher");
    g_signal_connect (button, "clicked", show_recherche, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,500,100);
    g_signal_connect (button, "clicked", NULL, win);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    view = gtk_tree_view_new();
    gtk_widget_set_size_request (view, 300,300);
    store = gtk_list_store_new (5,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"ID",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Cin",renderer,"text", 1,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Nom",renderer,"text", 2, NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Prenom",renderer,"text", 3,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Competence",renderer,"text", 4,NULL);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
    gtk_container_add (GTK_CONTAINER(scrollbar), view);

    gtk_widget_set_size_request (scrollbar, 600,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,30,160);

    gtk_widget_show_all (win);

}

/******************************** Gérer compitance *****************************************************/

void acc_com_user(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value1,*value2;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view1) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value1,  -1);
    gtk_tree_model_get(model, &iter, 1, &value2,  -1);

    printf("%d %d",atoi(value1),atoi(value2));

    if(acc_com_user_db(atoi(value1),atoi(value2))==-1)
    {
        show_error_invalide(p,"\nErreur ! verifier donnée");
    }
    else
    {
        app_info_succ_dialog(p,"\nCompetence Accepter !");
        storeC = gtk_list_store_new (4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
        show_compitance_id_encour(storeC, iter);
        gtk_tree_view_set_model (GTK_TREE_VIEW (view1), GTK_TREE_MODEL(storeC));
    }
}

void ref_com_user(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value1,*value2;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view1) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value1,  -1);
    gtk_tree_model_get(model, &iter, 1, &value2,  -1);

    printf("%d %d",atoi(value1),atoi(value2));

    if(ref_com_user_db(atoi(value1),atoi(value2))==-1)
    {
        show_error_invalide(p,"\nErreur ! verifier donnée");
    }
    else
    {
        app_info_succ_dialog(p,"\nCompetence Refuser !");
        storeC = gtk_list_store_new (4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
        show_compitance_id_encour(storeC, iter);
        gtk_tree_view_set_model (GTK_TREE_VIEW (view1), GTK_TREE_MODEL(storeC));
    }
}

void del_com_user(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value1,*value2;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view1) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value1,  -1);
    gtk_tree_model_get(model, &iter, 1, &value2,  -1);

    printf("%d %d",atoi(value1),atoi(value2));

    if(del_com_user_db(atoi(value1),atoi(value2))==-1)
    {
        show_error_invalide(p,"\nErreur ! verifier donnée");
    }
    else
    {
        app_info_succ_dialog(p,"\nCompetence Supprimer !");
        storeC = gtk_list_store_new (4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
        show_compitance_id_encour(storeC, iter);
        gtk_tree_view_set_model (GTK_TREE_VIEW (view1), GTK_TREE_MODEL(storeC));
    }
}

void acc_dip_user(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value1,*value2;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view2) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value1,  -1);
    gtk_tree_model_get(model, &iter, 1, &value2,  -1);

    printf("%d %d",atoi(value1),atoi(value2));

    if(acc_dip_user_db(atoi(value1),atoi(value2))==-1)
    {
        show_error_invalide(p,"\nErreur ! verifier donnée");
    }
    else
    {
        app_info_succ_dialog(p,"\nDiplome Accepter !");
        storeD = gtk_list_store_new (5,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
        show_dip_id_encour(storeD, iter);
        gtk_tree_view_set_model (GTK_TREE_VIEW (view2), GTK_TREE_MODEL(storeD));
    }
}

void ref_dip_user(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value1,*value2;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view2) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value1,  -1);
    gtk_tree_model_get(model, &iter, 1, &value2,  -1);

    printf("%d %d",atoi(value1),atoi(value2));

    if(ref_dip_user_db(atoi(value1),atoi(value2))==-1)
    {
        show_error_invalide(p,"\nErreur ! verifier donnée");
    }
    else
    {
        app_info_succ_dialog(p,"\nDiplome Refuser !");
        storeD = gtk_list_store_new (5,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
        show_dip_id_encour(storeD, iter);
        gtk_tree_view_set_model (GTK_TREE_VIEW (view2), GTK_TREE_MODEL(storeD));
    }
}

void del_dip_user(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value1,*value2;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view2) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value1,  -1);
    gtk_tree_model_get(model, &iter, 1, &value2,  -1);

    printf("%d %d",atoi(value1),atoi(value2));

    if(del_dip_user_db(atoi(value1),atoi(value2))==-1)
    {
        show_error_invalide(p,"\nErreur ! verifier donnée");
    }
    else
    {
        app_info_succ_dialog(p,"\nDiplome Supprimer !");
        storeD = gtk_list_store_new (5,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
        show_dip_id_encour(storeD, iter);
        gtk_tree_view_set_model (GTK_TREE_VIEW (view2), GTK_TREE_MODEL(storeD));
    }
}

void gerer_com_dip(GtkWidget *win,gpointer p)
{
    GtkWidget *text_view,*text_view2;
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *info,*espace,*lcnss,*lemail,*lnumerotel,*lville,*ladresse,*lpwd_u;
    GtkWidget *combo;
    GtkWidget *acc = NULL,*ref = NULL,*dell = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    GtkWidget *scrollbar = NULL;

    GtkCellRenderer     *renderer;
    GtkTreeModel        *model,*modelD;
    GtkTreeIter iter,iterD;
    gtk_widget_set_size_request (view, 300, 250);

    int id = Getsession();

    gtk_widget_hide(p);
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 750, 450);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Gérer Competence");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);

    menubar = gtk_menu_bar_new();
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    /******************* Competence *****************/
    view1 = gtk_tree_view_new ();
    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Gérer Competence: </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,10);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    storeC = gtk_list_store_new (4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"IDc",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"IDemp",renderer,"text", 1,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"Employe",renderer,"text", 2,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"Competence",renderer,"text", 3,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);

    show_compitance_id_encour(storeC, iter);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view1), GTK_TREE_MODEL(storeC));
    gtk_container_add (GTK_CONTAINER(scrollbar), view1);
    gtk_widget_set_size_request (scrollbar, 300,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,50,50);

    hbox = gtk_hbox_new (TRUE, 6);
    dell = gtk_button_new_with_label ("Supprimer");
    g_signal_connect (dell, "clicked",del_com_user, win);
    gtk_box_pack_start (GTK_BOX (hbox), dell, FALSE, TRUE, 0);
    ref = gtk_button_new_with_label ("Refuser");
    g_signal_connect (ref, "clicked", ref_com_user, win);
    gtk_box_pack_start (GTK_BOX (hbox), ref, FALSE, TRUE, 0);
    acc = gtk_button_new_with_label ("Accepter");
    g_signal_connect (acc, "clicked", acc_com_user, win);
    gtk_box_pack_start (GTK_BOX (hbox), acc, FALSE, TRUE, 0);

    gtk_fixed_put(GTK_FIXED(fixed),hbox,60,260);

    /******************* Diplome *****************/

    view2 = gtk_tree_view_new ();
    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Gérer Diplome: </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,400,10);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    storeD = gtk_list_store_new (5,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"IDc",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"IDemp",renderer,"text", 1,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"Employe",renderer,"text", 2,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"Diplome",renderer,"text", 3,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"Anné",renderer,"text", 4,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);

    show_dip_id_encour(storeD, iter);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view2), GTK_TREE_MODEL(storeD));
    gtk_container_add (GTK_CONTAINER(scrollbar), view2);
    gtk_widget_set_size_request (scrollbar, 320,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,400,50);

    hbox = gtk_hbox_new (TRUE, 6);
    dell = gtk_button_new_with_label ("Supprimer");
    g_signal_connect (dell, "clicked",del_dip_user, win);
    gtk_box_pack_start (GTK_BOX (hbox), dell, FALSE, TRUE, 0);
    ref = gtk_button_new_with_label ("Refuser");
    g_signal_connect (ref, "clicked", ref_dip_user, win);
    gtk_box_pack_start (GTK_BOX (hbox), ref, FALSE, TRUE, 0);
    acc = gtk_button_new_with_label ("Accepter");
    g_signal_connect (acc, "clicked", acc_dip_user, win);
    gtk_box_pack_start (GTK_BOX (hbox), acc, FALSE, TRUE, 0);

    gtk_fixed_put(GTK_FIXED(fixed),hbox,420,260);


    /**********************************************/

    gtk_widget_show_all (win);
}

/******************************** Gérer lic *********************************************************/

void dismissal(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(licempview) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 5, &value,  -1);
    if(strcmp(value,"Employe")==0)
    {
        gtk_tree_model_get(model, &iter, 0, &value,  -1);
        dismissal_user(atoi(value));
    }
    g_free(value);
    store = gtk_list_store_new (6,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    show_emps_lic(store,iter);
    gtk_tree_view_set_model (GTK_TREE_VIEW (licempview), GTK_TREE_MODEL(store));
}

void remp(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(licempview) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 5, &value,  -1);
    if(strcmp(value,"Employe congedie")==0)
    {
        gtk_tree_model_get(model, &iter, 0, &value,  -1);
        reemp_user(atoi(value));
    }
    g_free(value);
    store = gtk_list_store_new (6,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    show_emps_lic(store,iter);
    gtk_tree_view_set_model (GTK_TREE_VIEW (licempview), GTK_TREE_MODEL(store));
}



void gerer_lic(GtkWidget *win,gpointer p)
{

    gtk_widget_hide(p);
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL,*text_view2;
    GtkWidget *scrollbar = NULL;
    GtkWidget *info = NULL;
    GtkWidget *hbox,*vbox;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Gérer Licenciements");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 450);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Gérer Licenciements : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,25);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    licempview = gtk_tree_view_new();
    gtk_widget_set_size_request (licempview, 300,300);
    store = gtk_list_store_new (6,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (licempview),-1,"ID",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (licempview),-1,"Cin",renderer,"text", 1,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (licempview),-1,"Nom",renderer,"text", 2, NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (licempview),-1,"Prenom",renderer,"text", 3,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (licempview),-1,"CNSS",renderer,"text", 4,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (licempview),-1,"Etat",renderer,"text", 5,NULL);

    show_emps_lic(store,iter);

    gtk_tree_view_set_model (GTK_TREE_VIEW (licempview), GTK_TREE_MODEL(store));
    gtk_container_add (GTK_CONTAINER(scrollbar), licempview);

    gtk_widget_set_size_request (scrollbar, 600,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,30,70);

    hbox = gtk_hbox_new (TRUE, 6);
    button = gtk_button_new_with_label ("re-employer");
    g_signal_connect (button, "clicked",remp, win);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);
    button = gtk_button_new_with_label ("expulsion");
    g_signal_connect (button, "clicked", dismissal, win);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);

    gtk_fixed_put(GTK_FIXED(fixed),hbox,380,300);

    gtk_widget_show_all (win);

}

/******************************** Gérer Congé *********************************************************/

void accepter_vec(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value,  -1);
    accepter_vec_db(atoi(value));
    g_free(value);
    store = gtk_list_store_new (7,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    show_conge_emp(store,iter);
    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
}

void refus_vec(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;

    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value,  -1);
    refus_vec_db(atoi(value));
    g_free(value);
    store = gtk_list_store_new (7,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    show_conge_emp(store,iter);
    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
}


void gerer_vec(GtkWidget *win,gpointer p)
{

    gtk_widget_hide(p);
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL,*text_view2;
    GtkWidget *scrollbar = NULL;
    GtkWidget *info = NULL;
    GtkWidget *hbox,*vbox;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Gérer Congé");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 450);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Gérer Congé : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,25);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    view = gtk_tree_view_new();
    gtk_widget_set_size_request (view, 300,300);
    store = gtk_list_store_new (7,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"ID",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Cin",renderer,"text", 1,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Nom",renderer,"text", 2, NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Prenom",renderer,"text", 3,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Debut congé",renderer,"text", 4,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Fin congé",renderer,"text", 5,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Raison",renderer,"text", 6,NULL);

    show_conge_emp(store,iter);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
    gtk_container_add (GTK_CONTAINER(scrollbar), view);

    gtk_widget_set_size_request (scrollbar, 600,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,30,70);

    hbox = gtk_hbox_new (TRUE, 6);
    button = gtk_button_new_with_label ("Refuser");
    g_signal_connect (button, "clicked",refus_vec, win);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);
    button = gtk_button_new_with_label ("Accepter");
    g_signal_connect (button, "clicked", accepter_vec, win);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);

    gtk_fixed_put(GTK_FIXED(fixed),hbox,450,300);

    gtk_widget_show_all (win);

}

/******************************** Gérer fiche de paie *********************************************************/

void valid_modifier_salaire(GtkWidget *win,gpointer p)
{
    gchar *ss = gtk_entry_get_text(GTK_ENTRY(salaire) );
    update_salaire(ss,id);
    gtk_widget_hide(p);
}

void modifier_salaire(GtkWidget *win,gpointer p)
{
    employe *emp = malloc (sizeof (employe));
    GtkWidget *espace,*info;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    char *value;


    gchar gcin[100],gnom[100],gprenom[100],gcnss[100],gsalaire[100];


    selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(view) );
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);
    gtk_tree_model_get(model, &iter, 0, &value,  -1);
    id = atoi(value);
    get_user(emp,id);
    strcpy(gcin,emp->cinn);
    strcpy(gnom,emp->nom);
    strcpy(gprenom,emp->prenom);
    strcpy(gcnss,emp->cnss);

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Fiche de paie");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Fiche de paie : </b>\n\n");

    espace = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    info = gtk_label_new("Cin : ");
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    info = gtk_label_new(gcin);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    info = gtk_label_new("Nom : ");
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    info = gtk_label_new(gnom);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    info = gtk_label_new("Prenom : ");
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    info = gtk_label_new(gprenom);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    info = gtk_label_new("CNSS : ");
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    info = gtk_label_new(gcnss);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    get_salaire(gsalaire,id);

    info = gtk_label_new("Salaire : ");
    salaire =  gtk_entry_new();
    gtk_entry_set_text(salaire,gsalaire);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), salaire, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
    info = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);
    ok = gtk_button_new_with_label ("Modifier");
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    g_signal_connect (ok, "clicked",valid_modifier_salaire, win);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void gerer_fichedepai(GtkWidget *win,gpointer p)
{

    gtk_widget_hide(p);
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL,*text_view2;
    GtkWidget *scrollbar = NULL;
    GtkWidget *info = NULL;
    GtkWidget *hbox,*vbox;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Gérer fiche de paie");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 450);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Gérer fiche de paie : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,25);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    view = gtk_tree_view_new();
    gtk_widget_set_size_request (view, 300,300);
    store = gtk_list_store_new (5,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"ID",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Cin",renderer,"text", 1,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Nom",renderer,"text", 2, NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Prenom",renderer,"text", 3,NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"CNSS",renderer,"text", 4,NULL);

    show_emps_fich(store,iter);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
    gtk_container_add (GTK_CONTAINER(scrollbar), view);

    gtk_widget_set_size_request (scrollbar, 600,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,30,70);

    hbox = gtk_hbox_new (TRUE, 6);
    button = gtk_button_new_with_label ("Modifier");
    g_signal_connect (button, "clicked",modifier_salaire, win);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);


    gtk_fixed_put(GTK_FIXED(fixed),hbox,550,300);

    gtk_widget_show_all (win);

}

/******************************** Créer Menu *****************************************************/

void creer_home_res(GtkWidget *win)
{
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL;
    GtkWidget* text = NULL;
    GtkWidget *vbox;
    GtkWidget *image = NULL;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Espace Responsable");
    gtk_window_set_default_size(GTK_WINDOW(win), 850, 550);
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar_r(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_r(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/user_res.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", gerer_empl, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,50,25);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/skills_res.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", gerer_com_dip, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,310,25);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/search_res.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", chercher_emp, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,570,25);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/lic_res.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", gerer_lic, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,50,250);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/vec_res.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", gerer_vec, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,310,250);

    button = gtk_button_new();
    image = gtk_image_new_from_file("images/fiche_res.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", gerer_fichedepai, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,570,250);


    gtk_widget_show_all (win);
}
