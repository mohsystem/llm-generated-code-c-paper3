#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

PGconn* createPostgresConnection(const char* host, int port, const char* dbname, const char* user, const char* password) {
    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%d dbname=%s user=%s password=%s", host, port, dbname, user, password);

    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Error creating connection: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    return conn;
}

int main() {
    const char* host = "localhost";
    int port = 5432;
    const char* dbname = "testdb";
    const char* user = "postgres";
    const char* password = "cohondob";

    // Test cases
    for (int i = 0; i < 5; i++) {
        PGconn* conn = createPostgresConnection(host, port, dbname, user, password);
        if (conn) {
            printf("Connection created successfully\n");
            PQfinish(conn);
        }
    }

    return 0;
}