#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void registerUser(const char* name, const char* email, const char* password) {
    // Validate input
    if (strlen(name) == 0 || strlen(email) == 0 || strlen(password) < 8) {
        printf("Invalid input\n");
        return;
    }

    // Hash the password
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashedPassword, &sha256);

    MYSQL* conn;
    conn = mysql_init(0);
    if (!mysql_real_connect(conn, "localhost", "root", "", "users", 0, NULL, 0)) {
        printf("Error connecting to database: %s\n", mysql_error(conn));
        return;
    }

    char query[300];
    sprintf(query, "INSERT INTO userdata (username, email, password) VALUES ('%s', '%s', '%s')", name, email, hashedPassword);
    if (mysql_query(conn, query)) {
        printf("Error registering user: %s\n", mysql_error(conn));
    } else {
        printf("User registered successfully\n");
    }

    mysql_close(conn);
}

int main() {
    registerUser("John Doe", "john.doe@example.com", "password123");
    registerUser("Jane Doe", "jane.doe@example.com", "password456");
    return 0;
}