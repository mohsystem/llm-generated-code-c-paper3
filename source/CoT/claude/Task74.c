
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>

PGconn* getConnection(const char* host, const char* dbName, const char* user, const char* password) {
    // Allocate buffer for connection string
    char connInfo[512];
    
    // Create connection string
    snprintf(connInfo, sizeof(connInfo), 
             "host=%s dbname=%s user=%s password=%s port=5432",
             host, dbName, user, password);
    
    // Establish connection
    PGconn* conn = PQconnectdb(connInfo);
    
    // Check connection status
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection failed: %s\\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    
    return conn;
}

int main() {
    // Test cases
    const char* host = "localhost";
    const char* dbName = "testdb";
    const char* user = "postgres";
    const char* password = "password123";

    // Test case 1: Valid connection parameters
    PGconn* conn1 = getConnection(host, dbName, user, password);
    printf("Test 1: %s\\n", conn1 ? "Connection successful" : "Connection failed");
    if(conn1) PQfinish(conn1);

    // Test case 2: Invalid host
    PGconn* conn2 = getConnection("invalidhost", dbName, user, password);
    printf("Test 2: %s\\n", conn2 ? "Connection successful" : "Connection failed");
    if(conn2) PQfinish(conn2);

    // Test case 3: Invalid database name
    PGconn* conn3 = getConnection(host, "invaliddb", user, password);
    printf("Test 3: %s\\n", conn3 ? "Connection successful" : "Connection failed");
    if(conn3) PQfinish(conn3);

    // Test case 4: Invalid username
    PGconn* conn4 = getConnection(host, dbName, "invaliduser", password);
    printf("Test 4: %s\\n", conn4 ? "Connection successful" : "Connection failed");
    if(conn4) PQfinish(conn4);

    // Test case 5: Invalid password
    PGconn* conn5 = getConnection(host, dbName, user, "invalidpass");
    printf("Test 5: %s\\n", conn5 ? "Connection successful" : "Connection failed");
    if(conn5) PQfinish(conn5);

    return 0;
}
