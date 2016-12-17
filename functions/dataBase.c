#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void Connectdb(MYSQL *con)
{
    char sr[30],dbu[30],dbpass[30];
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    get_conf_file(sr,dbu,dbpass);
    if (mysql_real_connect(con, sr, dbu, dbpass,
                           "GRH", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
}
