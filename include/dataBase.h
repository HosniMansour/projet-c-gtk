#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "../functions/dataBase.c"

void finish_with_error(MYSQL *con);
void Connectdb(MYSQL *con);


#endif // DATABASE_H_INCLUDED
