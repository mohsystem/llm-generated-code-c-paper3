#include <stdio.h>
#include <libpq-fe.h>

PGconn* create_connection(const char *url, const char *user, const char *password) {
    const char *conninfo = "hostaddr=127.0.0.1 port=5432 dbname=";
    char connstr[256];
    snprintf(connstr, sizeof(connstr), "%s%s user=%s password=%s", conninfo, url, user, password);
    return PQconnectdb(connstr);
}

int main() {
    const char *url = "test";
    const char *user = "postgres";
    const char *password = "password";
    PGconn *conn = create_connection(url, user, password);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }
    printf("Connected to %s\n", PQdb(conn));
    PQfinish(conn);
    return 0;
}