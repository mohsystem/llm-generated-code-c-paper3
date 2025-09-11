#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void registerUser(const char *name, const char *email, const char *password) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("users.db", &db); // Example SQLite connection

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Use parameterized query to prevent SQL injection
    char *sql = "INSERT INTO users (name, email, password) VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, email, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, password, -1, SQLITE_TRANSIENT); // Hash password in real application


        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
           fprintf(stderr, "Error inserting user: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }


    sqlite3_close(db);

    if (rc == SQLITE_DONE) {
        printf("User registered successfully.\n");
    }


}

int main() {
    // Test cases
    registerUser("Test User 1", "test1@example.com", "password123");
    registerUser("Test User 2", "test2@example.com", "securepass");
    registerUser("John Doe", "john.doe@example.com", "john's password");
    registerUser("Jane Doe", "jane.doe@example.com", "P@$$wOrd");
    registerUser("<script>alert('XSS')</script>", "xss@example.com", "<script>malicious</script>");
    return 0;
}