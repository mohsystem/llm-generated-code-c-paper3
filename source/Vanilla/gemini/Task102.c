#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>

void hash_password(const char* password, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}


void update_password(const char* username, const char* new_password) {
    char hashed_password[65];
    hash_password(new_password, hashed_password);

    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init failed\n");
        return;
    }

    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database_name", 3306, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "UPDATE users SET password = '%s' WHERE username = '%s'", hashed_password, username);


    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query failed: %s\n", mysql_error(conn));
    }

    mysql_close(conn);
}

int main() {
    update_password("user1", "new_password1");
    update_password("user2", "new_password2");
    update_password("user3", "new_password3");
    update_password("user4", "new_password4");
    update_password("user5", "new_password5");
    return 0;
}