#include <stdio.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>

char* hashPassword(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char* hashedPassword = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
    return hashedPassword;
}

void updatePassword(const char* username, const char* newPassword) {
    char* hashedPassword = hashPassword(newPassword);
    if (hashedPassword != NULL) {
        MYSQL* connection = mysql_init(0);
        if (mysql_real_connect(connection, "localhost", "username", "password", "database", 0, NULL, 0)) {
            char sql[256];
            sprintf(sql, "UPDATE users SET password = '%s' WHERE username = '%s'", hashedPassword, username);
            if (mysql_query(connection, sql)) {
                printf("Password updated successfully\n");
            } else {
                printf("User not found\n");
            }
        } else {
            printf("Failed to connect to database\n");
        }
        mysql_close(connection);
        free(hashedPassword);
    }
}

int main() {
    updatePassword("user1", "newPassword");
    return 0;
}