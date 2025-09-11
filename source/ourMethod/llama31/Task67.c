#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

void getCustomerInfo(const char* customerUsername, sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* query = "SELECT * FROM customer WHERE customerusername = ?";
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }
    rc = sqlite3_bind_text(stmt, 1, customerUsername, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("Customer Info:\n");
        printf("Username: %s\n", sqlite3_column_text(stmt, 0));
        printf("Name: %s\n", sqlite3_column_text(stmt, 1));
        printf("Email: %s\n", sqlite3_column_text(stmt, 2));
        // Add other fields as needed
    } else {
        printf("Customer not found\n");
    }
    sqlite3_finalize(stmt);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <customerusername>\n", argv[0]);
        return 1;
    }
    const char* customerUsername = argv[1];
    sqlite3* db;
    int rc = sqlite3_open("yourdb.db", &db);
    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    getCustomerInfo(customerUsername, db);
    sqlite3_close(db);
    return 0;
}