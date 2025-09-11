#include <stdio.h>
#include <sqlite3.h>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    return 0;
}

int create_table(const char* db_name) {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "email TEXT UNIQUE NOT NULL, "
                      "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
    return 1;
}

int register_user(const char* db_name, const char* name, const char* email, const char* password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    int isRegistered = 0;

    rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char* sql = "INSERT INTO users (name, email, password) VALUES (?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            isRegistered = 1;
        }

        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return isRegistered;
}

int main() {
    const char* db_name = "userdb.sqlite";

    create_table(db_name);

    // Test cases
    printf("%d\n", register_user(db_name, "Alice", "alice@example.com", "securePassword1"));
    printf("%d\n", register_user(db_name, "Bob", "bob@example.com", "securePassword2"));
    printf("%d\n", register_user(db_name, "Charlie", "charlie@example.com", "securePassword3"));
    printf("%d\n", register_user(db_name, "David", "david@example.com", "securePassword4"));
    printf("%d\n", register_user(db_name, "Eve", "eve@example.com", "securePassword5"));

    return 0;
}