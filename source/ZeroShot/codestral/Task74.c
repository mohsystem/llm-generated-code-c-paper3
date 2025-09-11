#include <stdio.h>
#include <libpq-fe.h>

PGconn* createConnection(const char *dbname, const char *user, const char *password, const char *hostaddr, const char *port) {
    const char *conn_str = "dbname='%s' user='%s' password='%s' hostaddr='%s' port='%s'";
    PGconn *conn = PQconnectdb(conn_str, dbname, user, password, hostaddr, port);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    return conn;
}

int main() {
    PGconn *conn = createConnection("dbname", "user", "password", "localhost", "5432");
    if (conn != NULL) {
        printf("Connected to %s\n", PQdb(conn));

        // use the connection

        PQfinish(conn);
    } else {
        return 1;
    }

    return 0;
}