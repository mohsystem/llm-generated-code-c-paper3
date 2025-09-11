#include <stdio.h>
#include <libpq-fe.h>
#include <string.h>

PGconn* getPostgresConnection(const char* url, const char* user, const char* password) {
    // Extract connection parameters from the URL
    char pghost[256], pgport[32], pgdatabase[256];
    sscanf(url, "postgresql://%[^:]:%[^/]/%s", pghost, pgport, pgdatabase);

    // Build the connection string
    char conninfo[1024];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s", pghost, pgport, pgdatabase, user, password);

    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn); // Clean up the connection attempt in case of failure.
        return NULL;
    }

    return conn;
}


int main() {
    const char* url = "postgresql://localhost:5432/your_database_name";
    const char* user = "your_username";
    const char* password = "your_password";


    for (int i = 1; i <= 5; i++) {
         PGconn *conn = getPostgresConnection(url, user, password);

        if (conn) {
            printf("Test %d: Connection successful\n", i);
            PQfinish(conn);
        }
    }

    return 0;
}