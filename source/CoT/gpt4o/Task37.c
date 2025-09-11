#include <stdio.h>
#include <sqlite3.h>

void getUserInfo(const char *username) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("your_database.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *query = "SELECT * FROM users WHERE username = ?";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%s: %s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1));
        }
        sqlite3_finalize(stmt);
    }
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