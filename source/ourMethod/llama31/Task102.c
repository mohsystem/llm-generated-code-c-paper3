#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <bcrypt/BCrypt.h>

void hashPassword(const char* password, char* hashedPassword) {
    BCrypt_hashpw(password, hashedPassword, 12);
}

void updatePasswordInDatabase(const char* username, const char* hashedPassword) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("your_database.db", &db);
    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sql = "UPDATE users SET password = ? WHERE username = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, hashedPassword, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Password updated successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char username[100], newPassword[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter new password: ");
    scanf("%99s", newPassword);

    char hashedPassword[100];
    hashPassword(newPassword, hashedPassword);
    updatePasswordInDatabase(username, hashedPassword);

    return 0;
}