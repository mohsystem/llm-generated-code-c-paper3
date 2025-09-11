#include <stdio.h>
#include <libpq.h>
#include <string.h>

PGconn *getPostgresConnection(const char *url, const char *user, const char *password) {

    char conninfo[256]; // Adjust size as needed
    snprintf(conninfo, sizeof(conninfo), "hostaddr=%s port=%s dbname=%s user=%s password=%s",
            strtok((char *)url+strlen("postgresql://"),":"), strtok(NULL, "/"), strtok(NULL,""), user, password);



    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    return conn;
}

int main() {
    const char *url = "postgresql://localhost:5432/your_database_name"; // Replace with your database URL
    const char *user = "your_username"; // Replace with your username
    const char *password = "your_password"; // Replace with your password

    for (int i = 1; i <= 5; i++) {
        PGconn *conn = getPostgresConnection(url, user, password);
        if (conn) {
            printf("Test %d: Connection successful\n", i);
            PQfinish(conn);
        }
    }
    return 0;
}