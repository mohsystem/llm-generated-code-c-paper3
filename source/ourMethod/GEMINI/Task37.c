#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sqlite3.h>

// Initializes the database with a users table and some sample data
bool initializeDatabase(sqlite3* db) {
    const char* create_table_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "email TEXT NOT NULL,"
        "full_name TEXT NOT NULL);";

    const char* insert_data_sql =
        "INSERT OR IGNORE INTO users(username, email, full_name) VALUES"
        "('alice', 'alice@example.com', 'Alice Smith'),"
        "('bob', 'bob@example.com', 'Bob Johnson');";

    char* err_msg = NULL;
    int rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        return false;
    }

    rc = sqlite3_exec(db, insert_data_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

// Validates the username format (3-16 alphanumeric characters)
bool isValidUsername(const char* username) {
    if (username == NULL) {
        return false;
    }
    size_t len = strlen(username);
    if (len < 3 || len > 16) {
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        if (!((username[i] >= 'a' && username[i] <= 'z') ||
              (username[i] >= 'A' && username[i] <= 'Z') ||
              (username[i] >= '0' && username[i] <= '9'))) {
            return false;
        }
    }
    return true;
}

// Retrieves user information for a given username using a prepared statement.
void getUserInfo(sqlite3* db, const char* username) {
    if (!isValidUsername(username)) {
        printf("Invalid username format.\n");
        return;
    }

    const char* sql = "SELECT id, username, email, full_name FROM users WHERE username = ?;";
    sqlite3_stmt* stmt = NULL;
    // Use sqlite3_prepare_v2 for safety and modern features.
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        printf("Error preparing query.\n");
        return;
    }

    // Bind the user-provided username as a text parameter.
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameter: %s\n", sqlite3_errmsg(db));
        printf("Error binding parameter.\n");
        sqlite3_finalize(stmt); // Clean up the statement
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("User Found:\n");
        printf("  ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("  Username: %s\n", sqlite3_column_text(stmt, 1));
        printf("  Email: %s\n", sqlite3_column_text(stmt, 2));
        printf("  Full Name: %s\n", sqlite3_column_text(stmt, 3));
    } else if (rc == SQLITE_DONE) {
        printf("User not found: %s\n", username);
    } else {
        fprintf(stderr, "Failed to step statement: %s\n", sqlite3_errmsg(db));
        printf("Error executing query.\n");
    }

    sqlite3_finalize(stmt); // Always finalize the statement to release resources.
}

void runTestCase(sqlite3* db, const char* testName, const char* username) {
    printf("%s: Searching for '%s'\n", testName, username);
    getUserInfo(db, username);
    printf("--------------------\n");
}

int main(void) {
    // NOTE: To compile this file, you need to link against the sqlite3 library.
    // Example: gcc your_file.c -o your_program -lsqlite3
    
    sqlite3* db = NULL;
    int rc = sqlite3_open(":memory:", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (!initializeDatabase(db)) {
        sqlite3_close(db);
        return 1;
    }

    printf("--- Test Cases ---\n");

    // Test Case 1: Valid, existing user
    runTestCase(db, "Test 1", "alice");

    // Test Case 2: Another valid, existing user
    runTestCase(db, "Test 2", "bob");

    // Test Case 3: Valid, but non-existent user
    runTestCase(db, "Test 3", "charlie");

    // Test Case 4: Invalid username format (contains symbols)
    runTestCase(db, "Test 4", "user@");

    // Test Case 5: Classic SQL injection attempt.
    // This is safely handled by the prepared statement.
    runTestCase(db, "Test 5", "admin' OR '1'='1'");
    
    sqlite3_close(db);
    return 0;
}