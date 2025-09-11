#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void getUserInfo(const char* username) {
    sqlite3* db;
    int exit = sqlite3_open("mydatabase.db", &db);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sql = "SELECT * FROM users WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("User ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("Username: %s\n", sqlite3_column_text(stmt, 1));
        printf("Email: %s\n", sqlite3_column_text(stmt, 2));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    getUserInfo("user1");
    getUserInfo("user2");
    getUserInfo("user3");
    getUserInfo("user4");
    getUserInfo("user5");
    return 0;
}