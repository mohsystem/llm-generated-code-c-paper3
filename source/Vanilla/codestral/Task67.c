#include <stdio.h>
#include <sqlite3.h>

char* getCustomerInfo(const char* customerUsername) {
    sqlite3* DB;
    sqlite3_open("your_database.db", &DB);

    char sql[256];
    sprintf(sql, "SELECT * FROM customer WHERE username = '%s'", customerUsername);
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Assuming you have columns "name" and "email" in your customer table
        char* name = (char*)sqlite3_column_text(stmt, 1);
        char* email = (char*)sqlite3_column_text(stmt, 2);

        char result[256];
        sprintf(result, "Name: %s, Email: %s", name, email);
        return strdup(result);
    } else {
        char result[256];
        sprintf(result, "No customer found with username: %s", customerUsername);
        return strdup(result);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

int main(int argc, char* argv[]) {
    printf("%s\n", getCustomerInfo(argv[1]));
    return 0;
}