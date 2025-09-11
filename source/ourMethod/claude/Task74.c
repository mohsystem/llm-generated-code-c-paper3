
#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PGconn* get_connection(const char* host, const char* port, const char* database,
                      const char* username, const char* password) {
    if (!host || !port || !database || !username || !password) {
        fprintf(stderr, "Connection parameters cannot be NULL\\n");
        return NULL;
    }

    char conninfo[1024];
    snprintf(conninfo, sizeof(conninfo),
             "host=%s port=%s dbname=%s user=%s password=%s",
             host, port, database, username, password);

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\\n",
                PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    return conn;
}

int main() {
    // Test case 1 - Valid connection
    PGconn *conn1 = get_connection("localhost", "5432", "testdb", "user", "password");
    if (conn1) {
        printf("Test 1: Connection successful\\n");
        PQfinish(conn1);
    }

    // Test case 2 - Invalid host
    PGconn *conn2 = get_connection("invalidhost", "5432", "testdb", "user", "password");
    if (conn2) PQfinish(conn2);

    // Test case 3 - Invalid port
    PGconn *conn3 = get_connection("localhost", "1234", "testdb", "user", "password");
    if (conn3) PQfinish(conn3);

    // Test case 4 - Invalid credentials
    PGconn *conn4 = get_connection("localhost", "5432", "testdb", "invalid", "invalid");
    if (conn4) PQfinish(conn4);

    // Test case 5 - NULL parameters
    PGconn *conn5 = get_connection(NULL, "5432", "testdb", "user", "password");
    if (conn5) PQfinish(conn5);

    return 0;
}
