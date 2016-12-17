#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "../include/TypeDef.h"
#include "../include/dataBase.h"


int verifierLoginPwd(char * login, char * pwd)
{

    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"%s%s%s%s%s","SELECT * FROM Utilisateur WHERE username='",login,"' and password='",pwd,"';");
    if (mysql_query(con,querry))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        finish_with_error(con);
    }
    MYSQL_ROW row=mysql_fetch_row(result);
    int res=(row==NULL)?-1:0;
    if(res==0)
    {
        if(strcmp(row[13],"role_admin")==0)
        {
            res=1;
        }
        else if(strcmp(row[13],"Employe")==0)
        {
            if(strcmp(row[14],"Employe congedie")==0)
            {
                res=-2;
            }
            else
            {
                res=2;
            }
        }
        else if(strcmp(row[13],"Responsable")==0)
        {
            res=3;
        }
    }
    mysql_free_result(result);
    mysql_close(con);
    return res;
}

int getiduser(char * login, char * pwd)
{

    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"%s%s%s%s%s","SELECT * FROM Utilisateur WHERE username='",login,"' and password='",pwd,"';");
    if (mysql_query(con,querry))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        finish_with_error(con);
    }
    MYSQL_ROW row=mysql_fetch_row(result);
    int res = atoi(row[0]);
    return res;
}


int add_user_db(employe emp)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"insert into Utilisateur(id,cin,username,password,nom,prenom,dns,cnss,sexe,email,num_tel,ville,adresse,role) Values(NULL,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','Employe');",
            emp.cinn,emp.username,emp.pwd_u,emp.nom,emp.prenom,emp.dns,emp.cnss,emp.sexe,emp.email,emp.numerotel,emp.ville,emp.adresse);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    sendmail(emp.email,emp.nom,emp.username,emp.pwd_u);
    mysql_close(con);
}

int add_res_db(employe emp)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"insert into Utilisateur(id,cin,username,password,nom,prenom,dns,cnss,sexe,email,num_tel,ville,adresse,role) Values(NULL,'%s','%s','%s','%s','%s',NULL,NULL,NULL,'%s',NULL,NULL,NULL,'%s');",
            emp.cinn,emp.username,emp.pwd_u,emp.nom,emp.prenom,emp.email,emp.role);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    mysql_close(con);
}

int update_emp(employe emp,int id)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update Utilisateur set cin='%s',username='%s',password='%s',nom='%s',prenom='%s',dns='%s',cnss='%s',sexe='%s',email='%s',num_tel='%s',ville='%s',adresse='%s' where id = %d ;",
            emp.cinn,emp.username,emp.pwd_u,emp.nom,emp.prenom,emp.dns,emp.cnss,emp.sexe,emp.email,emp.numerotel,emp.ville,emp.adresse,id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int update_emp_user(employe emp,int id)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update Utilisateur set cnss='%s',password='%s',email='%s',num_tel='%s',ville='%s',adresse='%s' where id = %d ;",
            emp.cnss,emp.pwd_u,emp.email,emp.numerotel,emp.ville,emp.adresse,id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int update_responsable(employe emp,int id)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update Utilisateur set cin='%s',username='%s',password='%s',nom='%s',prenom='%s',email='%s' where id = %d ;",
            emp.cinn,emp.username,emp.pwd_u,emp.nom,emp.prenom,emp.email,id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

void delete_user(int id)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"delete from Utilisateur where id=%d;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    mysql_close(con);
}

void show_users(GtkListStore  *store,GtkTreeIter iter)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    if (mysql_query(con, "select * from Utilisateur;"))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,COL_ID, row[0],COL_NOM, row[4],COL_PRENOM, row[5],COL_ROLE, row[13],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

int dismissal_user(int id)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update Utilisateur set etat='Employe congedie' where id = %d ;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int reemp_user(int id)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update Utilisateur set etat='Employe' where id = %d ;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int update_exp_lang(int id,char *s1,char *s2)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[800];
    sprintf(querry,"update Utilisateur set experience='%s', lang='%s' where id = %d ;",s1,s2,id);
    printf("\n%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

void show_emps_lic(GtkListStore  *store,GtkTreeIter iter)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    if (mysql_query(con, "select * from Utilisateur where role = 'Employe';"))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1, row[1],2, row[4],3, row[5],4,row[7],5,row[14],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void getexperience_lang(int id,GtkWidget *t1,GtkWidget *t2)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select id,experience,lang from Utilisateur where id = %d;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        row = mysql_fetch_row(result);
        gtk_entry_set_text(t1,row[1]);
        gtk_entry_set_text(t2,row[2]);
        mysql_free_result(result);
    }
    mysql_close(con);
}

int init_salaire(int id)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"insert into salaire(id_sal,id_emp,montant) Values(NULL,%d,'-');",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    mysql_close(con);
}

int insert_diplome_user(int id,char *t1,char *t2)
{
    int res=0;
    int id2;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"insert into diplome(id,nomD,anne) Values(NULL,'%s','%s');",t1,t2);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }

    if (mysql_query(con,"SELECT MAX(id) FROM diplome;"))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        finish_with_error(con);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row=mysql_fetch_row(result);
    id2=atoi(row[0]);
    strcpy(querry,"");
    sprintf(querry,"insert into utilisateur_diplome(id_u,id_d,etat) Values(%d,%d,'0');",id,id2);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    mysql_close(con);
}

int insert_com_user(int id,char *t1)
{
    int res=0;
    int id2;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"insert into competence(id,nomc) Values(NULL,'%s');",t1);
    printf("\n%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }

    if (mysql_query(con,"SELECT MAX(id) FROM competence;"))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        finish_with_error(con);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row=mysql_fetch_row(result);
    id2=atoi(row[0]);
    strcpy(querry,"");
    sprintf(querry,"insert into utilisateur_competence(id_u,id_c,etat) Values(%d,%d,'0');",id,id2);
    printf("\n%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    mysql_close(con);
}

int add_cong_db(int id,char *d1,char *d2,char *raison)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"insert into conge(id,id_emp,date_deb,date_fin,etat,raison) Values(NULL,%d,'%s','%s','en cour','%s');",id,d1,d2,raison);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    mysql_close(con);
}

int update_salaire(char *mont,int id)
{
    int res=0;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update salaire set montant='%s' where id_emp = %d ;",mont,id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    mysql_close(con);
}

void show_emps_fich(GtkListStore  *store,GtkTreeIter iter)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    if (mysql_query(con, "select * from Utilisateur where role = 'Employe' and etat='Employe' ;"))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1, row[1],2, row[4],3, row[5],4,row[7],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_all_cong(GtkListStore  *store,GtkTreeIter iter,int id)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select * from conge where id_emp = %d ;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1, row[2],2, row[3],3, row[4],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_compitance_id(GtkListStore  *store,GtkTreeIter iter,int id)
{
    char *etat;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select * from utilisateur_competence t1, competence t2 where t1.id_c = t2.id and t1.id_u = %d ;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            if(strcmp(row[2],"1")==0)
            {
                etat="Validé";
            }
            else if(strcmp(row[2],"-1")==0)
            {
                etat="Refusé";
            }
            else
            {
                etat="En cour";
            }
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[1],1,row[4],2, etat,-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_compitance_id_encour(GtkListStore  *store,GtkTreeIter iter)
{
    char *etat;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    if (mysql_query(con, "select t1.*,t2.*,t3.nom,t3.prenom from utilisateur_competence t1, competence t2, Utilisateur t3 where t1.id_c = t2.id and t1.etat = '0' and t3.id=t1.id_u;"))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100]="Hosni Mansour";
        while ((row = mysql_fetch_row(result)))
        {
            sprintf(user_info,"%s %s",row[5],row[6]);
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1,row[1],2,user_info,3,row[4],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_compitance_id_valid(int id)
{
    char ch[200];
    char cmd[100];
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select t1.*,t2.*,t3.nom,t3.prenom from utilisateur_competence t1, competence t2, Utilisateur t3 where t1.id_c = t2.id and t1.etat = '1' and t3.id=t1.id_u and t1.id_u=%d;",id);
    if (mysql_query(con,querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            sprintf(cmd,"sed -i 's#<comp>#<li itemprop=\'itemListElement\'>%s</li><comp>#g' /tmp/cv%d/index.html",row[4],id);
            system(cmd);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_diplome_id_valid(int id)
{
    char ch[200];
    char cmd[100];
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select t1.*,t2.*,t3.nom,t3.prenom from utilisateur_diplome t1, diplome t2, Utilisateur t3 where t1.id_d = t2.id and t1.etat = '1' and t3.id=t1.id_u and t1.id_u=%d;",id);
    if (mysql_query(con,querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            sprintf(cmd,"sed -i 's#<dipl>#<p><span itemprop=\'alumniOf\'>%s %s</p><dipl>#g' /tmp/cv%d/index.html",row[4],row[5],id);
            system(cmd);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_dip_id_encour(GtkListStore  *store,GtkTreeIter iter)
{
    char *etat;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    if (mysql_query(con, "select t1.*,t2.*,t3.nom,t3.prenom from utilisateur_diplome t1, diplome t2, Utilisateur t3 where t1.id_d = t2.id and t1.etat = '0' and t3.id=t1.id_u;"))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100]="Hosni Mansour";
        while ((row = mysql_fetch_row(result)))
        {
            sprintf(user_info,"%s %s",row[6],row[7]);
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1,row[1],2,user_info,3,row[4],4,row[5],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_diplome_id(GtkListStore  *store,GtkTreeIter iter,int id)
{
    char *etat;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select * from utilisateur_diplome t1, diplome t2 where t1.id_d = t2.id and t1.id_u = %d ;",id);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            if(strcmp(row[2],"1")==0)
            {
                etat="Validé";
            }
            else if(strcmp(row[2],"-1")==0)
            {
                etat="Refusé";
            }
            else
            {
                etat="En cour";
            }
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[1],1,row[4],2, etat,-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void searsh_skill_db(GtkListStore  *store,GtkTreeIter iter,char *keyword)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[200];
    sprintf(querry,"select * from Utilisateur t1, competence t2, utilisateur_competence t3 where t1.id = t3.id_u and t2.id=t3.id_c and t2.nomc like '%c%s%c';",37,keyword,37);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1, row[1],2, row[4],3, row[5],4, row[18],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

int acc_com_user_db(int idc,int idu)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update utilisateur_competence set etat='1' where id_u = %d and id_c = %d ;",idc,idu);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int ref_com_user_db(int idc,int idu)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update utilisateur_competence set etat='-1' where id_u = %d and id_c = %d ;",idc,idu);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int del_com_user_db(int idc,int idu)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"delete from utilisateur_competence where id_u = %d and id_c = %d ;",idc,idu);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}


/************************/

int acc_dip_user_db(int idc,int idu)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update utilisateur_diplome set etat='1' where id_u = %d and id_d = %d ;",idc,idu);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int ref_dip_user_db(int idc,int idu)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update utilisateur_diplome set etat='-1' where id_u = %d and id_d = %d ;",idc,idu);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int del_dip_user_db(int idc,int idu)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"delete from utilisateur_diplome where id_u = %d and id_d = %d ;",idc,idu);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

/************************/

int accepter_vec_db(int id)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update conge set etat='accepter' where id = %d ;",id);
    printf("%s",querry);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

int refus_vec_db(int id)
{
    int res;
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[350];
    sprintf(querry,"update conge set etat='refuser' where id = %d ;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
        res = -1;
    }
    else
    {
        res = 1;
    }
    return res;
    mysql_close(con);
}

void show_conge_emp(GtkListStore  *store,GtkTreeIter iter)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[300];
    if (mysql_query(con, "select t1.*, t2.* from Utilisateur t1, conge t2 where t1.id = t2.id_emp and t2.etat = 'en cour';"))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        char user_info[100];
        while ((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set(store, &iter,0, row[0],1, row[1],2, row[4],3, row[5],4,row[19],5,row[20],6,row[22],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void get_salaire(gchar *gsalaire,int id)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[100];
    sprintf(querry,"select montant from salaire where id_emp=%d;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row = mysql_fetch_row(result);
        if(row==NULL)
        {
            init_salaire(id);
            strcpy(gsalaire,"-");
        }
        else
        {
            strcpy(gsalaire,row[0]);
        }

    }
}


void get_user(employe *emp,int id)
{
    MYSQL *con = mysql_init(NULL);
    Connectdb(con);
    char querry[500];
    sprintf(querry,"select * from Utilisateur where id=%d;",id);
    if (mysql_query(con, querry))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row = mysql_fetch_row(result);
        emp->id = row[0];
        emp->cinn = row[1];
        emp->username = row[2];
        emp->pwd_u = row[3];
        emp->nom = row[4];
        emp->prenom = row[5];
        emp->dns = row[6];
        emp->cnss = row[7];
        emp->sexe = row[8];
        emp->email = row[9];
        emp->numerotel = row[10];
        emp->ville = row[11];
        emp->adresse = row[12];
        emp->role = row[13];
        emp->expe = row[15];
        emp->lnnnn = row[16];

        mysql_free_result(result);
    }
}
