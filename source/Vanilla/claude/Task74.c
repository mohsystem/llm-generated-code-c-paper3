
#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PGconn* getPostgresConnection(const char* url, const char* username, const char* password) {
    char conninfo[512];
    // Parse JDBC URL to extract host, port, and database
    char host[256], port[8], dbname[256];
    
    // Simple parsing (assumes URL format: jdbc:postgresql://host:port/dbname)
    sscanf(url, "jdbc:postgresql://%[^:]:%[^/]/%s", host, port, dbname);
    
    snprintf(conninfo, sizeof(conninfo), 
             "host=%s port=%s dbname=%s user=%s password=%s",
             host, port, dbname, username, password);

    PGconn* conn = PQconnectdb(conninfo);
    
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection failed: %s\\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    
    return conn;
}

int main() {
    // Test cases
    const char* testUrls[] = {
        "jdbc:postgresql://localhost:5432/testdb",
        "jdbc:postgresql://192.168.1.1:5432/proddb",
        "jdbc:postgresql://localhost:5432/devdb",
        "jdbc:postgresql://remotehost:5432/qadb",
        "jdbc:postgresql://localhost:5432/stagingdb"
    };
    const char* testUsers[] = {"user1", "admin", "dev", "qa", "stage"};
    const char* testPasswords[] = {"pass1", "admin123", "dev123", "qa123", "stage123"};

    for(int i = 0; i < 5; i++) {
        PGconn* conn = getPostgresConnection(testUrls[i], testUsers[i], testPasswords[i]);
        if(conn != NULL) {
            printf("Test case %d: Connection successful\\n", i+1);
            PQfinish(conn);
        } else {
            printf("Test case %d: Connection failed\\n", i+1);
        }
    }

    return 0;
}
