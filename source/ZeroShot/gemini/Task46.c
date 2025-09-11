#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int registerUser(const char* name, const char* email, const char* password) {
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open("users.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* createTableSql = "CREATE TABLE IF NOT EXISTS users (name TEXT, email TEXT UNIQUE, password TEXT)";
    rc = sqlite3_exec(db, createTableSql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char insertSql[512]; // Adjust size as needed
    snprintf(insertSql, sizeof(insertSql), "INSERT INTO users (name, email, password) VALUES ('%s', '%s', '%s')", name, email, password);

    rc = sqlite3_exec(db, insertSql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        if(rc == SQLITE_CONSTRAINT_UNIQUE) {
            fprintf(stderr, "Error: Email %s already exists.\n", email);
        } else {
             fprintf(stderr, "SQL error: %s\n", err_msg);
             sqlite3_free(err_msg);
        }
        sqlite3_close(db);
        return 1;
    }


    sqlite3_close(db);
    return 0;
}

int main() {
    registerUser("John Doe", "john.doe@example.com", "password123");
    registerUser("Jane Smith", "jane.smith@example.com", "securepass");
    registerUser("Peter Jones", "peter.jones@example.com", "p@$$wOrd");
    registerUser("Alice Brown", "alice.brown@example.com", "al1c3");
    registerUser("Bob Green", "bob.green@example.com", "b0bgR33n");

    return 0;
}