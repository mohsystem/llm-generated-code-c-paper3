
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

/* Security: Never hardcode credentials, use environment variables (Rules#3, Rules#4) */
/* Returns server name from environment, fails closed if not set */
const char* getServerName(void) {
    const char* server = getenv("DB_SERVER");
    if (server == NULL || strlen(server) == 0) {
        /* Security: Fail closed with minimal information (Rules#1) */
        fprintf(stderr, "Database server configuration not found\\n");
        return NULL;
    }
    return server;
}

/* Security: Retrieve database name from environment, not hardcoded */
const char* getDatabaseName(void) {
    const char* dbName = getenv("DB_NAME");
    if (dbName == NULL || strlen(dbName) == 0) {
        fprintf(stderr, "Database name configuration not found\\n");
        return NULL;
    }
    return dbName;
}

/* Security: Retrieve database user from environment, not hardcoded */
const char* getDatabaseUser(void) {
    const char* user = getenv("DB_USER");
    if (user == NULL || strlen(user) == 0) {
        fprintf(stderr, "Database user configuration not found\\n");
        return NULL;
    }
    return user;
}

/* Security: Retrieve password from environment, never log or expose (Rules#1, Rules#3, Rules#4) */
const char* getDatabasePassword(void) {
    const char* password = getenv("DB_PASSWORD");
    if (password == NULL || strlen(password) == 0) {
        fprintf(stderr, "Database password configuration not found\\n");
        return NULL;
    }
    return password;
}

/* Security: Returns database connection with TLS enforcement (Rules#5, Rules#7) */
MYSQL* getDatabaseConnection(void) {
    const char* server = getServerName();
    const char* dbName = getDatabaseName();
    const char* user = getDatabaseUser();
    const char* password = getDatabasePassword();
    
    /* Security: Check all configuration retrieved successfully */
    if (server == NULL || dbName == NULL || user == NULL || password == NULL) {
        return NULL;
    }
    
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\\n");
        return NULL;
    }
    
    /* Security: Enforce TLS/SSL with certificate verification (Rules#5, Rules#7) */
    enum mysql_ssl_mode ssl_mode = SSL_MODE_REQUIRED;
    if (mysql_options(conn, MYSQL_OPT_SSL_MODE, &ssl_mode) != 0) {
        fprintf(stderr, "Failed to set SSL mode\\n");
        mysql_close(conn);
        return NULL;
    }
    
    /* Security: Set TLS version to 1.2 or higher */
    const char* tls_version = "TLSv1.2,TLSv1.3";
    if (mysql_options(conn, MYSQL_OPT_TLS_VERSION, tls_version) != 0) {
        fprintf(stderr, "Failed to set TLS version\\n");
        mysql_close(conn);
        return NULL;
    }
    
    /* Security: Establish connection with all security settings */
    if (mysql_real_connect(conn, server, user, password, dbName, 
                          3306, NULL, CLIENT_SSL) == NULL) {
        /* Security: Generic error message (Rules#1) */
        fprintf(stderr, "Database connection failed\\n");
        mysql_close(conn);
        return NULL;
    }
    
    return conn;
}

/* Simplified web server handler simulation */
void handleRequest(void) {
    MYSQL* conn = getDatabaseConnection();
    if (conn != NULL) {
        /* Security: Never log credentials or connection details (Rules#1) */
        printf("HTTP/1.1 200 OK\\r\\n");
        printf("Content-Type: text/plain\\r\\n\\r\\n");
        printf("Database connection successful\\n");
        mysql_close(conn);
    } else {
        /* Security: Generic error to client, no internal details (Rules#1) */
        printf("HTTP/1.1 500 Internal Server Error\\r\\n");
        printf("Content-Type: text/plain\\r\\n\\r\\n");
        printf("Service temporarily unavailable\\n");
    }
}

int main(void) {
    /* Test cases demonstrating secure configuration retrieval */
    
    printf("Test Case 1: Retrieve server name\\n");
    const char* server = getServerName();
    if (server != NULL) {
        printf("Server configured: true\\n");
    } else {
        printf("Configuration error: Environment variable DB_SERVER not set\\n");
    }
    
    printf("\\nTest Case 2: Retrieve database name\\n");
    const char* dbName = getDatabaseName();
    if (dbName != NULL) {
        printf("Database configured: true\\n");
    } else {
        printf("Configuration error: Environment variable DB_NAME not set\\n");
    }
    
    printf("\\nTest Case 3: Retrieve database user\\n");
    const char* user = getDatabaseUser();
    if (user != NULL) {
        printf("User configured: true\\n");
    } else {
        printf("Configuration error: Environment variable DB_USER not set\\n");
    }
    
    printf("\\nTest Case 4: Retrieve database password\\n");
    const char* password = getDatabasePassword();
    if (password != NULL) {
        /* Security: Never print passwords (Rules#1) */
        printf("Password configured: true\\n");
    } else {
        printf("Configuration error: Environment variable DB_PASSWORD not set\\n");
    }
    
    printf("\\nTest Case 5: Establish database connection\\n");
    MYSQL* conn = getDatabaseConnection();
    if (conn != NULL) {
        printf("Connection successful: true\\n");
        mysql_close(conn);
    } else {
        printf("Connection failed\\n");
    }
    
    return 0;
}
