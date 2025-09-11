#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

char* getUserInfo(const char* username) {
    char* result = NULL;
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM users WHERE username = ?";

    if (sqlite3_open("mydatabase.db", &db) != SQLITE_OK) {
        return "Cannot open database";
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return "Failed to prepare statement";
    }

    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "Failed to bind parameter";
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = "User found";
    } else {
        result = "User not found";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}

int main() {
    printf("%s\n", getUserInfo("john"));
    printf("%s\n", getUserInfo("doe"));
    printf("%s\n", getUserInfo("alice"));
    printf("%s\n", getUserInfo("bob"));
    printf("%s\n", getUserInfo("charlie"));
    return 0;
}