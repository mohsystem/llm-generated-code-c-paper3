#include <stdio.h>
#include <libpq-fe.h>

PGconn* getPostgresConnection(const char* url, const char* user, const char* password) {
    PGconn* conn = PQconnectdbParams((char*[]){"host", (char*)url.split("/")[2].split(":")[0] , "port", (char*)url.split("/")[2].split(":")[1], "user", (char*)user, "password", (char*)password, "dbname", (char*)url.split("/")[-1], NULL}, NULL, 0);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    return conn;
}

int main() {
    // Replace with your PostgreSQL database credentials
      char* url = "postgresql://localhost:5432/your_database_name";
    char* user = "your_username";
    char* password = "your_password";

    for (int i = 1; i <= 5; i++) {
        PGconn *conn = getPostgresConnection(url, user, password);
        if (conn) {
            printf("Test %d: Connection successful!\n", i);
            PQfinish(conn);
        }
    }

    return 0;
}