#include <stdio.h>
#include <sqlite3.h>

void createUser(const char* name, const char* email) {
    sqlite3* db;
    char* errMsg = 0;
    int rc = sqlite3_open("testdb.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS users (name TEXT, email TEXT);";
    char sqlInsert[256];
    snprintf(sqlInsert, sizeof(sqlInsert), "INSERT INTO users (name, email) VALUES ('%s', '%s');", name, email);

    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sqlInsert, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}

int main() {
    createUser("John Doe", "john.doe@example.com");
    createUser("Jane Smith", "jane.smith@example.com");
    createUser("Alice Johnson", "alice.johnson@example.com");
    createUser("Bob Brown", "bob.brown@example.com");
    createUser("Charlie White", "charlie.white@example.com");
    return 0;
}