/* C does not have built-in support for Postgres connections.
 * This example uses the libpq library, which is a C library for connecting to Postgres.
 * The code below assumes that libpq is installed and can be linked.
 */

#include <libpq-fe.h>
#include <stdio.h>

PGconn* create_postgres_connection(const char *url, const char *user, const char *password) {
    return PQconnectdb(url);
}

int main() {
    const char *url = "dbname=test user=user password=password";
    const char *user = "user";
    const char *password = "password";

    PGconn *conn = create_postgres_connection(url, user, password);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    printf("Connected to Postgres database.\n");
    PQfinish(conn);

    return 0;
}