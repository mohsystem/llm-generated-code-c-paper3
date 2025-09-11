#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>

void getUserInfo(const char* username) {
    const char *conninfo = "dbname=your_database user=your_username password=your_password hostaddr=127.0.0.1 port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    const char *query = "SELECT * FROM your_table WHERE username = $1";
    const char *paramValues[1];
    paramValues[0] = username;
    int paramLengths[1];
    paramLengths[0] = strlen(username);
    int paramFormats[1];
    paramFormats[0] = 0;

    PGresult *res = PQexecParams(conn, query, 1, NULL, paramValues, paramLengths, paramFormats, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "No data retrieved\n");
        PQclear(res);
    } else {
        for (int i = 0; i < PQntuples(res); i++) {
            printf("%s %s\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1));
        }
        PQclear(res);
    }

    PQfinish(conn);
}

int main() {
    getUserInfo("testUser");
    return 0;
}