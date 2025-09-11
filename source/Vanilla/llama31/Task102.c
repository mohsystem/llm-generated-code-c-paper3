#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
}

void updatePassword(const char* username, const char* newPassword, const char* dbUrl, const char* dbUser, const char* dbPassword) {
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    hashPassword(newPassword, hashedPassword);

    MYSQL* conn;
    conn = mysql_init(0);
    if (!mysql_real_connect(conn, dbUrl, dbUser, dbPassword, "mydb", 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return;
    }

    char query[256];
    sprintf(query, "UPDATE users SET password = '%s' WHERE username = '%s'", hashedPassword, username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error updating password: %s\n", mysql_error(conn));
    }

    mysql_close(conn);
}

int main() {
    const char* dbUrl = "localhost";
    const char* dbUser = "myuser";
    const char* dbPassword = "mypassword";
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    const char* newPassword = "newpassword";

    for (int i = 0; i < 5; ++i) {
        updatePassword(usernames[i], newPassword, dbUrl, dbUser, dbPassword);
    }

    return 0;
}