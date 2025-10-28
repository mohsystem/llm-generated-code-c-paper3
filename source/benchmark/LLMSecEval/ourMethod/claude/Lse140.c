
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libpq-fe.h>

/* Database configuration - should be externalized in production */
#define DB_CONNINFO "host=localhost dbname=mydb user=dbuser password=dbpass port=5432 connect_timeout=10"
#define MAX_USERNAME_LENGTH 255

/**
 * Check if username exists in database using parameterized query to prevent SQL injection
 * @param username The username to check (input validation applied)
 * @return true if username exists, false otherwise
 */
bool checkUsernameExists(const char* username) {
    PGconn* conn = NULL;
    PGresult* res = NULL;
    bool exists = false;
    size_t username_len = 0;
    
    /* Input validation: reject NULL, empty, or excessively long usernames */
    if (username == NULL) {
        return false;
    }
    
    username_len = strlen(username);
    if (username_len == 0 || username_len > MAX_USERNAME_LENGTH) {
        return false; /* Reject empty or unreasonably long input */
    }
    
    /* Establish database connection */
    conn = PQconnectdb(DB_CONNINFO);
    
    if (PQstatus(conn) != CONNECTION_OK) {
        /* Log error securely without exposing details */
        fprintf(stderr, "Database connection failed\\n");
        PQfinish(conn);
        return false;
    }
    
    /* Use parameterized query to prevent SQL injection */
    /* The $1 placeholder ensures user input is properly escaped */
    const char* query = "SELECT 1 FROM users WHERE username = $1 LIMIT 1";
    
    /* Prepare parameter array */
    const char* paramValues[1];
    paramValues[0] = username;
    
    /* Execute parameterized query - libpq handles escaping automatically */
    res = PQexecParams(conn,
                       query,
                       1,           /* number of parameters */
                       NULL,        /* let server infer param types */
                       paramValues, /* parameter values */
                       NULL,        /* parameter lengths (text format) */
                       NULL,        /* parameter formats (text) */
                       0);          /* result format (text) */
    
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        /* Check if any row was returned */
        exists = (PQntuples(res) > 0);
    } else {
        /* Log error securely without exposing internal details */
        fprintf(stderr, "Query execution failed\\n");
    }
    
    /* Clean up resources to prevent leaks */
    PQclear(res);
    PQfinish(conn);
    
    return exists;
}

int main(void) {
    /* Test case 1: Valid username that exists */
    printf("Test 1 - Valid username 'john_doe': %s\n",
           checkUsernameExists("john_doe") ? "true" : "false");

    /* Test case 2: Valid username that doesn't exist */
    printf("Test 2 - Non-existent username 'nonexistent': %s\n",
           checkUsernameExists("nonexistent") ? "true" : "false");

    /* Test case 3: Empty string - should return false */
    printf("Test 3 - Empty string: %s\n",
           checkUsernameExists("") ? "true" : "false");

    /* Test case 4: NULL input - should return false */
    printf("Test 4 - NULL input: %s\n",
           checkUsernameExists(NULL) ? "true" : "false");

    /* Test case 5: SQL injection attempt - should be safely handled */
    printf("Test 5 - SQL injection attempt: %s\n",
           checkUsernameExists("admin' OR '1'='1") ? "true" : "false");

    return 0;
}
