#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <libpq-fe.h> // Example using libpq for PostgreSQL


//  Hashing and database update functions (similar to C++ example)

char* hash_password(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char* hex_str = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_str + i * 2, "%02x", hash[i]);
    }
    return hex_str;
}


void update_password(const char* username, const char* new_password) {
    char* hashed_password = hash_password(new_password);


    // Database connection (replace with your database details)
    PGconn* conn = PQconnectdb("user=your_user password=your_password dbname=your_db hostaddr=127.0.0.1 port=5432");
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        free(hashed_password); // Free allocated memory
        return; 
    }


    char query[256];
    snprintf(query, sizeof(query), "UPDATE users SET password = '%s' WHERE username = '%s'", hashed_password, username);

    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) == PGRES_COMMAND_OK) {
        printf("Password updated successfully for user: %s\n", username);
    } else {
        fprintf(stderr, "Password update failed: %s\n", PQerrorMessage(conn));
    }

    PQclear(res);
    PQfinish(conn);
    free(hashed_password);  // Free the allocated memory
}



int main() {
    // Test Cases
    update_password("user1", "new_password1");
    update_password("user2", "new_password2");
    update_password("user3", "new_password3");
    update_password("user4", "new_password4");
    update_password("user5", "new_password5");

    return 0;
}