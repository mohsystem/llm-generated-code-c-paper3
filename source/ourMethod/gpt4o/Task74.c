#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

PGconn* get_postgres_connection(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    return conn;
}

int main() {
    // Test cases
    const char* conninfo = "dbname=testdb user=testuser password=testpassword host=localhost port=5432";
    PGconn* conn = get_postgres_connection(conninfo);
    if (conn) {
        printf("Connection established.\n");
        PQfinish(conn);
    } else {
        printf("Failed to establish connection.\n");
    }
    return 0;
}