#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED

struct struct_employe
{
    int id;
    gchar *cinn,*username,*nom,*prenom,*dns,*cnss,*sexe,*email,*numerotel,*ville,*adresse,*pwd_u,*role,*lnnnn,*expe;
};
typedef struct struct_employe employe;

enum
{
    COL_ID=0,
    COL_NOM=1,
    COL_PRENOM=2,
    COL_ROLE=3,
    NUM_COLS
};

#endif // TYPEDEF_H_INCLUDED
