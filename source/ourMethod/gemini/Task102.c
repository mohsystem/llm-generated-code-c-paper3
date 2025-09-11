#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <libpq-fe.h>
#include <stdbool.h>

// ... (same hash_password function as in C++)

bool update_password(const char *username, const char *new_password) {
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    strcpy(hashed_password, hash_password(new_password).c_str());

    PGconn *conn = PQconnectdb("dbname=your_database_name user=your_db_user password=your_db_password");
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return false;
    }

    // Parameterized query to prevent SQL injection
    const char *query = "UPDATE users SET password = $1 WHERE username = $2";
    const char *values[2] = {hashed_password, username};
    int lengths[2] = {strlen(hashed_password), strlen(username)};
    int formats[2] = {0, 0}; // Text format for both parameters

    PGresult *res = PQexecParams(conn, query, 2, NULL, values, lengths, formats, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Update password failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return false;
    }

    PQclear(res);
    PQfinish(conn);
    return true;
}

int main() {
    // Test cases
    printf("Password updated: %s\n", update_password("testuser1", "password123") ? "true" : "false");
    printf("Password updated: %s\n", update_password("testuser2", "securepass") ? "true" : "false");
    printf("Password updated: %s\n", update_password("testuser3", "complexP@$$") ? "true" : "false");
    printf("Password updated: %s\n", update_password("testuser4", "anotherpass") ? "true" : "false");
    printf("Password updated: %s\n", update_password("testuser5", "test1234") ? "true" : "false");

    return 0;
}