#include <stdio.h>
#include <libpq-fe.h>

PGconn* create_postgres_connection(const char* host, const char* port, const char* dbname, const char* user, const char* password) {
    char conninfo[1024];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s", host, port, dbname, user, password);

    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    return conn;
}

int main() {
    const char* host = "localhost";
    const char* port = "5432";
    const char* dbname = "mydb";
    const char* user = "myuser";
    const char* password = "mypassword";

    PGconn* conn = create_postgres_connection(host, port, dbname, user, password);
    if (conn) {
        printf("Connected to PostgreSQL database\n");
        PQfinish(conn);
    } else {
        printf("Failed to connect to PostgreSQL database\n");
    }

    return 0;
}