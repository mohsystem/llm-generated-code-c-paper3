#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int storeUserData(const char *name, const char *email, int age) {
    sqlite3 *db;
    char *errmsg = 0;
    int rc = sqlite3_open(":memory:", &db); // Using in-memory DB for simplicity

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users (name TEXT, email TEXT, age INTEGER)";
    rc = sqlite3_exec(db, sql, 0, 0, &errmsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }

    sql = "INSERT INTO users (name, email, age) VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, age);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("User data stored successfully.\n");
    return 0;
}

int main() {
    storeUserData("John Doe", "john.doe@example.com", 30);
    storeUserData("Jane Smith", "jane.smith@example.com", 25);
    storeUserData("Peter Jones", "peter.jones@example.com", 40);
    storeUserData("Alice Brown", "alice.brown@example.com", 28);
    storeUserData("Bob Williams", "bob.williams@example.com", 35);

    return 0;
}