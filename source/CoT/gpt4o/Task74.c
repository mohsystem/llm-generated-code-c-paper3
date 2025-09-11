#include <stdio.h>
#include <libpq-fe.h>

PGconn* getPostgresConnection(const char* conninfo) {
    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    return conn;
}

int main() {
    const char* conninfo = "dbname=mydatabase user=myuser password=mypassword hostaddr=127.0.0.1 port=5432";

    // Test cases
    PGconn* conn1 = getPostgresConnection(conninfo);
    PGconn* conn2 = getPostgresConnection("dbname=mydatabase user=wronguser password=mypassword hostaddr=127.0.0.1 port=5432");
    PGconn* conn3 = getPostgresConnection("dbname=mydatabase user=myuser password=wrongpassword hostaddr=127.0.0.1 port=5432");
    PGconn* conn4 = getPostgresConnection("dbname=mydatabase user=myuser password=mypassword hostaddr=wronghost port=5432");
    PGconn* conn5 = getPostgresConnection(conninfo);

    printf("%s\n", conn1 ? "Connected" : "Failed");
    printf("%s\n", conn2 ? "Connected" : "Failed");
    printf("%s\n", conn3 ? "Connected" : "Failed");
    printf("%s\n", conn4 ? "Connected" : "Failed");
    printf("%s\n", conn5 ? "Connected" : "Failed");

    PQfinish(conn1);
    PQfinish(conn2);
    PQfinish(conn3);
    PQfinish(conn4);
    PQfinish(conn5);

    return 0;
}