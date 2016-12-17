#include <gtk/gtk.h>
#include "../include/TypeDef.h"


GtkWidget *edittext1,*edittext2,*cin,*nom,*prenom,*dns,*cnss,*sexe,*email,*numerotel,*ville,*adresse,*pwd_u,*un,*jour,*month,*year,*jourf,*monthf,*yearf,*raison;
GtkWidget *view,*view1,*view2;
GtkListStore  *store,*storeC,*storeD;

void close_window_e(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
}


void menu_u(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    close_window(win,p);
    creer_home_emp(win);
}

void logout_u(GtkWidget *win,gpointer p)
{
    gtk_widget_hide(p);
    gtk_widget_hide(win);
    authentification(win);
}

void about_info_u(GtkWidget *win,gpointer p)
{
    app_info_dialog(p);
}

void menu_bar_u(GtkWidget *menubar,GtkWidget *win)
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
    g_signal_connect(menuMI, "activate",menu_u,win);
    lougoutMI = gtk_image_menu_item_new_with_label("Se déconnecter");
    image = gtk_image_new_from_file("images/icon/logout.png");
    gtk_image_menu_item_set_image(lougoutMI, image);
    g_signal_connect(lougoutMI, "activate",logout_u,win);
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
    g_signal_connect(apropos, "activate",about_info_u,win);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(aide), aideMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(aideMenu), apropos);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), aide);
}

void getcv(GtkWidget *win,gpointer p)
{
    generatecv();
}

void toolbar_fn_u(GtkWidget *toolbar,GtkWidget *win)
{
    GtkWidget *sep;
    GtkToolItem *homeTb;
    GtkToolItem *cv;
    GtkToolItem *exitTb;
    GtkWidget *image;

    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    homeTb = gtk_tool_button_new_from_stock(GTK_STOCK_HOME);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), homeTb,-1);
    g_signal_connect(G_OBJECT(homeTb), "clicked",G_CALLBACK(menu_u), win);

    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    cv = gtk_tool_button_new_from_stock(GTK_STOCK_PRINT_PREVIEW);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), cv,-1);
    g_signal_connect(G_OBJECT(cv), "clicked",G_CALLBACK(getcv), win);

    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);
    g_signal_connect(G_OBJECT(exitTb), "clicked",G_CALLBACK(logout_u), win);
}


/******************************** Info Personelle *****************************************************/

void valid_mod_info_us(GtkWidget *win,gpointer *p)
{

    employe emp;
    int id = Getsession();
    emp.cnss = gtk_entry_get_text(GTK_ENTRY(cnss));
    emp.email = gtk_entry_get_text(GTK_ENTRY(email));
    emp.numerotel = gtk_entry_get_text(GTK_ENTRY(numerotel));
    emp.ville = gtk_entry_get_text(GTK_ENTRY(ville));
    emp.adresse = gtk_entry_get_text(GTK_ENTRY(adresse));
    emp.pwd_u = gtk_entry_get_text(GTK_ENTRY(pwd_u));

    if((strcmp(emp.numerotel,"")==0) || (strcmp(emp.pwd_u,"")==0))
    {
        show_error_invalide(p,"\nIl' y a des champs vide !");
    }
    else
    {
        if(update_emp_user(emp,id)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier les données");
        }
        else
        {
            app_info_succ_dialog(p,"\nModification effectuée avec succès ! ");
        }
    }


}

void modifier_info_per(GtkWidget *win,gpointer p)
{
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *info,*espace,*lcnss,*lemail,*lnumerotel,*lville,*ladresse,*lpwd_u;
    GtkWidget *combo;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    gchar gcnss[100],gemail[100],gnumerotel[100],gville[100],gadresse[100],gpwd_u[100];

    employe *emp = malloc (sizeof (employe));
    int id = Getsession();
    get_user(emp,id);
    strcpy(gemail,emp->email);
    strcpy(gnumerotel,emp->numerotel);
    strcpy(gcnss,emp->cnss);
    strcpy(gville,emp->ville);
    strcpy(gadresse,emp->adresse);
    strcpy(gpwd_u,emp->pwd_u);

    gtk_widget_hide(p);
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 400);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Modifier Information");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);

    menubar = gtk_menu_bar_new();
    menu_bar_u(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_u(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Modifier Information: </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,10);



    lemail = gtk_label_new("Email : ");
    email =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 0);
    gtk_entry_set_text(email,gemail);
    gtk_fixed_put(GTK_FIXED(fixed),lemail,20,75);
    gtk_fixed_put(GTK_FIXED(fixed),email,120,65);
    lpwd_u = gtk_label_new("Password : ");
    pwd_u =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 0);
    gtk_entry_set_text(pwd_u,gpwd_u);
    gtk_fixed_put(GTK_FIXED(fixed),lpwd_u,20,125);
    gtk_fixed_put(GTK_FIXED(fixed),pwd_u,120,115);


    lcnss = gtk_label_new("CNSS : ");
    cnss =  gtk_entry_new();
    gtk_entry_set_text(cnss,gcnss);
    gtk_fixed_put(GTK_FIXED(fixed),lcnss,340,75);
    gtk_fixed_put(GTK_FIXED(fixed),cnss,440,65);

    lnumerotel = gtk_label_new("Num Tel : ");
    numerotel =  gtk_entry_new();
    gtk_entry_set_text(numerotel,gnumerotel);
    gtk_fixed_put(GTK_FIXED(fixed),lnumerotel,340,125);
    gtk_fixed_put(GTK_FIXED(fixed),numerotel,440,115);

    lville = gtk_label_new("Ville : ");
    ville =  gtk_entry_new();
    gtk_entry_set_text(ville,gville);
    gtk_fixed_put(GTK_FIXED(fixed),lville,20,175);
    gtk_fixed_put(GTK_FIXED(fixed),ville,120,165);

    ladresse = gtk_label_new("Adresse : ");
    adresse =  gtk_entry_new();
    gtk_entry_set_text(adresse,gadresse);
    gtk_fixed_put(GTK_FIXED(fixed),ladresse,340,175);
    gtk_fixed_put(GTK_FIXED(fixed),adresse,440,165);

    hbox = gtk_hbox_new (TRUE, 6);
    ok = gtk_button_new_with_label ("Modifier");
    g_signal_connect (ok, "clicked",valid_mod_info_us, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", menu_u, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);
    gtk_fixed_put(GTK_FIXED(fixed),hbox,450,250);

    gtk_widget_show_all (win);
}


/******************************** Competance *****************************************************/

void valide_ajouter_user_com(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;

    char *t1 = gtk_entry_get_text(GTK_ENTRY(edittext1));
    int id = Getsession();

    if( strcmp(t1,"")==0 )
    {
        show_error_invalide(p,"\nChamp vide !");
    }
    else
    {
        if(insert_com_user(id,t1)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier donnée");
        }
        else
        {
            close_window(win,p);
            storeC = gtk_list_store_new (3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
            show_compitance_id(storeC,iter,id);
            gtk_tree_view_set_model (GTK_TREE_VIEW (view1), GTK_TREE_MODEL(storeC));
        }
    }
}

void ajouter_user_com(GtkWidget *win,gpointer p)
{
    GtkWidget *espace,*info;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;


    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Ajouter competence");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Ajouter competence : </b>\n\n");

    espace = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);


    info = gtk_label_new("Nom competence : ");
    edittext1 =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), edittext1, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
    info = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window_e, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);
    ok = gtk_button_new_with_label ("Ajouter");
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    g_signal_connect (ok, "clicked",valide_ajouter_user_com, win);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void valide_ajouter_user_diplome(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;

    char *t1 = gtk_entry_get_text(GTK_ENTRY(edittext1));
    char *t2 = gtk_entry_get_text(GTK_ENTRY(edittext2));
    int id = Getsession();

    if( strcmp(t1,"")==0 || strcmp(t2,"")==0 )
    {
        show_error_invalide(p,"\nChamp vide !");
    }
    else
    {
        if(insert_diplome_user(id,t1,t2)==-1)
        {
            show_error_invalide(p,"\nErreur ! verifier donnée");
        }
        else
        {
            close_window(win,p);
            storeD = gtk_list_store_new (3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
            show_diplome_id(storeD,iter,id);
            gtk_tree_view_set_model (GTK_TREE_VIEW (view2), GTK_TREE_MODEL(storeD));
        }
    }
}

void ajouter_user_diplome(GtkWidget *win,gpointer p)
{
    GtkWidget *espace,*info;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;


    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Ajouter competence");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_hide, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "\n<b>Ajouter competence : </b>\n\n");

    espace = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);


    info = gtk_label_new("Nom Diplome : ");
    edittext1 =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), edittext1, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    info = gtk_label_new("Année Diplome : ");
    edittext2 =  gtk_entry_new();
    hbox = gtk_hbox_new (TRUE, 6);
    gtk_box_pack_start (GTK_BOX (hbox), info, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), edittext2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    info = gtk_label_new("\n\n");
    gtk_box_pack_start (GTK_BOX (vbox), info, FALSE, FALSE, 0);

    hbox = gtk_hbox_new (TRUE, 6);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", close_window_e, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);
    ok = gtk_button_new_with_label ("Ajouter");
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    g_signal_connect (ok, "clicked",valide_ajouter_user_diplome, win);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all (win);
}

void valid_exp_lan(GtkWidget *win,gpointer p)
{

    char *s1 = gtk_entry_get_text(GTK_ENTRY(edittext1) );
    char *s2 = gtk_entry_get_text(GTK_ENTRY(edittext2) );
    int id = Getsession();
    update_exp_lang(id,s1,s2);

    app_info_succ_dialog(p,"\nInformation mis a jour !");

}

void modifier_com(GtkWidget *win,gpointer p)
{
    char *exp,*ll;

    GtkWidget *text_view,*text_view2,*info;
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    GtkWidget *scrollbar = NULL;

    GtkCellRenderer     *renderer,*rendererD;
    GtkTreeModel        *model,*modelD;
    GtkTreeIter iter,iterD;

    gtk_widget_hide(p);
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 650, 580);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Modifier Competence / Experience / Diplome ...");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);

    menubar = gtk_menu_bar_new();
    menu_bar_u(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_u(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    /******************* Competence *****************/

    int id = Getsession();

    view1 = gtk_tree_view_new ();
    gtk_widget_set_size_request (view1, 250, 250);


    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Modifier Competence: </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,10);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    storeC = gtk_list_store_new (3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"ID",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"Competence",renderer,"text", 1,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view1),-1,"Etat",renderer,"text", 2,NULL);
    gtk_tree_view_column_set_resizable(view1,TRUE);

    show_compitance_id(storeC,iter,id);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view1), GTK_TREE_MODEL(storeC));
    gtk_container_add (GTK_CONTAINER(scrollbar), view1);
    gtk_widget_set_size_request (scrollbar, 200,100);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,50,50);

    ok = gtk_button_new_with_label ("Ajouter");
    g_signal_connect (ok, "clicked",ajouter_user_com, win);
    gtk_fixed_put(GTK_FIXED(fixed),ok,230,160);

    /******************* Diplome *****************/
    view2 = gtk_tree_view_new ();
    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Modifier Diplome: </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,350,10);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    storeD = gtk_list_store_new (4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    rendererD = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"ID",rendererD,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);
    rendererD = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"Diplome",rendererD,"text", 1,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);
    rendererD = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view2),-1,"Etat",rendererD,"text", 2,NULL);
    gtk_tree_view_column_set_resizable(view2,TRUE);

    show_diplome_id(storeD, iterD,id);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view2), GTK_TREE_MODEL(storeD));
    gtk_container_add (GTK_CONTAINER(scrollbar), view2);
    gtk_widget_set_size_request (scrollbar, 250,100);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,350,50);

    ok = gtk_button_new_with_label ("Ajouter");
    g_signal_connect (ok, "clicked",ajouter_user_diplome, win);
    gtk_fixed_put(GTK_FIXED(fixed),ok,530,160);

    /********************* btn *************************/


    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Experience : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,200);


    edittext1 = gtk_entry_new();
    gtk_widget_set_size_request (edittext1, 550, 80);
    gtk_fixed_put(GTK_FIXED(fixed),edittext1,50,240);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Langue : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,340);

    edittext2 = gtk_entry_new();
    gtk_widget_set_size_request (edittext2, 550, 30);
    gtk_fixed_put(GTK_FIXED(fixed),edittext2,50,380);

    exp = getexperience_lang(id,edittext1,edittext2);



    hbox = gtk_hbox_new (TRUE, 6);
    ok = gtk_button_new_with_label ("Modifier");
    g_signal_connect (ok, "clicked",valid_exp_lan, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", menu_u, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);
    gtk_fixed_put(GTK_FIXED(fixed),hbox,450,450);

    gtk_widget_show_all (win);
}



/******************************** congé *****************************************************/

void valide_demande_cong(GtkWidget *win,gpointer p)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    char d1[30],d2[30];
    int id = Getsession();
    sprintf(d1,"%s/%s/%s",gtk_combo_box_text_get_active_text(jour),gtk_combo_box_text_get_active_text(month),gtk_combo_box_text_get_active_text(year));
    sprintf(d2,"%s/%s/%s",gtk_combo_box_text_get_active_text(jourf),gtk_combo_box_text_get_active_text(monthf),gtk_combo_box_text_get_active_text(yearf));
    add_cong_db(id,d1,d2,gtk_entry_get_text(GTK_ENTRY(raison)));
    app_info_succ_dialog(p,"\nVotre demande a éte envoyé ! ");
    store = gtk_list_store_new (4,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    show_all_cong(store,iter,id);
    gtk_tree_view_set_model (GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));

}

void demande_cong(GtkWidget *win,gpointer p)
{
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *ldated,*ldatef,*info,*lraison;
    GtkWidget *combo;
    GtkWidget *ok = NULL,*annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;

    GtkWidget *scrollbar = NULL;
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkTreeIter iter;

    view = gtk_tree_view_new ();
    gtk_widget_set_size_request (view, 250, 250);

    employe *emp = malloc (sizeof (employe));

    int id = Getsession();

    gtk_widget_hide(p);
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 700, 400);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Demande congé");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);

    menubar = gtk_menu_bar_new();
    menu_bar_u(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_u(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Demande congé : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,25,10);


    ldated = gtk_label_new("Date Debut : ");
    jour = gtk_combo_box_text_new();
    month = gtk_combo_box_text_new();
    year = gtk_combo_box_text_new();
    jour_month_year(jour,month,year);

    gtk_fixed_put(GTK_FIXED(fixed),ldated,50,75);
    gtk_fixed_put(GTK_FIXED(fixed),jour,170,65);
    gtk_fixed_put(GTK_FIXED(fixed),month,220,65);
    gtk_fixed_put(GTK_FIXED(fixed),year,270,65);


    ldatef = gtk_label_new("Date Fin : ");

    jourf = gtk_combo_box_text_new();
    monthf = gtk_combo_box_text_new();
    yearf = gtk_combo_box_text_new();
    jour_month_year(jourf,monthf,yearf);
    gtk_fixed_put(GTK_FIXED(fixed),ldatef,50,125);
    gtk_fixed_put(GTK_FIXED(fixed),jourf,170,125);
    gtk_fixed_put(GTK_FIXED(fixed),monthf,220,125);
    gtk_fixed_put(GTK_FIXED(fixed),yearf,270,125);

    lraison = gtk_label_new("Raison : ");
    raison =  gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),lraison,50,185);
    gtk_fixed_put(GTK_FIXED(fixed),raison,170,175);

    hbox = gtk_hbox_new (TRUE, 6);
    annuler = gtk_button_new_with_label ("Annuler");
    g_signal_connect (annuler, "clicked", menu_u, win);
    gtk_box_pack_start (GTK_BOX (hbox), annuler, FALSE, TRUE, 0);
    ok = gtk_button_new_with_label ("Demander");
    g_signal_connect (ok, "clicked",valide_demande_cong, win);
    gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, TRUE, 0);

    gtk_fixed_put(GTK_FIXED(fixed),hbox,170,250);


    /******************* list des congés *****************/

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Liste des congés : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,380,10);

    scrollbar = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

    store = gtk_list_store_new (4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"ID",renderer,"text", 0,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Date Debut",renderer,"text", 1,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Date Fin",renderer,"text", 2,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Etat",renderer,"text", 3,NULL);
    gtk_tree_view_column_set_resizable(view,TRUE);

    show_all_cong(store,iter,id);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));
    gtk_container_add (GTK_CONTAINER(scrollbar), view);
    gtk_widget_set_size_request (scrollbar, 150,200);
    gtk_fixed_put(GTK_FIXED(fixed),scrollbar,390,60);

    /**************************************************************/

    gtk_widget_show_all (win);
}


/******************************** Fichedepaie *****************************************************/

void demande_fichdepai(GtkWidget *win,gpointer p)
{
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar,*label,*labeltext;
    GtkWidget *info;
    GtkWidget *annuler = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *hbox = NULL;
    gchar  gidd[100]="",gcin[100]="",gnom[100]="",gprenom[100]="",gcnss[100]="",gsalaire[100]="";
    employe *emp = malloc (sizeof (employe));

    int id = Getsession();
    get_user(emp,id);
    sprintf(gidd,"%d",id);
    strcpy(gcin,emp->cinn);
    strcpy(gnom,emp->nom);
    strcpy(gprenom,emp->prenom);
    strcpy(gcnss,emp->cnss);

    gtk_widget_hide(p);
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 550, 400);
    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Fiche de paie");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    gtk_window_set_resizable(GTK_WINDOW(win),FALSE);

    vbox = gtk_vbox_new (FALSE, 6);

    menubar = gtk_menu_bar_new();
    menu_bar_u(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_u(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);

    gtk_container_add (GTK_CONTAINER (win), vbox);

    info = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info), "<b>Fiche de paie : </b>");
    gtk_fixed_put(GTK_FIXED(fixed),info,35,10);


    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Ref Emp :  </b>");
    labeltext = gtk_label_new(gidd);
    gtk_fixed_put(GTK_FIXED(fixed),label,80,75);
    gtk_fixed_put(GTK_FIXED(fixed),labeltext,190,75);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>CIN :  </b>");
    labeltext = gtk_label_new(gcin);
    gtk_fixed_put(GTK_FIXED(fixed),label,80,115);
    gtk_fixed_put(GTK_FIXED(fixed),labeltext,160,115);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Nom et Prenom employé :  </b>");
    char nomprenom[100];
    sprintf(nomprenom,"%s %s",gnom,gprenom);
    labeltext = gtk_label_new(nomprenom);
    gtk_fixed_put(GTK_FIXED(fixed),label,80,155);
    gtk_fixed_put(GTK_FIXED(fixed),labeltext,300,155);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>CNSS :  </b>");
    labeltext = gtk_label_new(gcnss);
    gtk_fixed_put(GTK_FIXED(fixed),label,80,200);
    gtk_fixed_put(GTK_FIXED(fixed),labeltext,160,200);

    get_salaire(gsalaire,id);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Salaire Net :  </b>");
    labeltext = gtk_label_new(gsalaire);
    gtk_fixed_put(GTK_FIXED(fixed),label,80,240);
    gtk_fixed_put(GTK_FIXED(fixed),labeltext,210,240);

    annuler = gtk_button_new_with_label ("Retour");
    g_signal_connect (annuler, "clicked", menu_u, win);
    gtk_fixed_put(GTK_FIXED(fixed),annuler,380,240);

    gtk_widget_show_all (win);
}


/******************************** Créer Menu *****************************************************/

void creer_home_emp(GtkWidget *win)
{
    GtkWidget *fixed;
    GtkWidget *menubar,*toolbar;
    GtkWidget *button = NULL;
    GtkWidget* text = NULL;
    GtkWidget *vbox;
    GtkWidget *image = NULL;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_container_set_border_width (GTK_CONTAINER (win), 0);
    gtk_window_set_title (GTK_WINDOW (win), "Espace Employé");
    gtk_window_set_default_size(GTK_WINDOW(win), 580, 550);
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    menubar = gtk_menu_bar_new();
    menu_bar_u(menubar,win);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    toolbar = gtk_toolbar_new();
    toolbar_fn_u(toolbar,win);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    fixed=gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 5);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/user.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", modifier_info_per, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,50,25);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/skills.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", modifier_com, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,310,25);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/vec.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", demande_cong, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,50,250);


    button = gtk_button_new();
    image = gtk_image_new_from_file("images/fiche.png");
    gtk_button_set_image(button,image);
    g_signal_connect (button, "clicked", demande_fichdepai, win);
    gtk_fixed_put(GTK_FIXED(fixed),button,310,250);

    gtk_widget_show_all (win);
}
