#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void update_password(const char *username, const char *new_password) {
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(new_password, hashed_password);


    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("your_database.db", &db); // Replace with your database file

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[512]; // Adjust size as needed
    snprintf(sql, sizeof(sql), "UPDATE users SET password = '%s' WHERE username = '%s'", hashed_password, username);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    sqlite3_close(db);
}


int main() {
    update_password("user1", "new_password1");
    update_password("user2", "new_password2");
    update_password("user3", "new_password3");
    update_password("user4", "new_password4");
    update_password("user5", "new_password5");

    return 0;
}