#include <libpq-fe.h>
#include <stdio.h>

PGconn* createConnection(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    return conn;
}

int main() {
    const char* conninfo = "host=localhost port=5432 dbname=test user=username password=password";
    PGconn* conn = createConnection(conninfo);
    if (conn) {
        // Use the connection here...
        PQfinish(conn);
    }
    return 0;
}