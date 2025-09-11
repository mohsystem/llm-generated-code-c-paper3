//  Similar to C++ implementation using SQLite. Replace SQLite code with your specific database interaction code
// and adapt the struct and error handling.


#include <stdio.h>
#include <string.h>
#include <sqlite3.h>


struct Customer {
    char customerusername[256]; // Adjust size as needed
    // ... other attributes
};


struct Customer get_customer(const char* customerusername) {
    sqlite3* db;
    int rc = sqlite3_open("your_database.db", &db); // Replace with your database file

    struct Customer customer = {};
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return customer; // Return empty Customer on error
    }

    sqlite3_stmt* stmt;
    char sql[256]; // Adjust as needed
    snprintf(sql, sizeof(sql), "SELECT * FROM customer WHERE customerusername = '%s'", customerusername); // Vulnerable to SQL injection if customerusername is not sanitized

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return customer;
    }
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        strcpy(customer.customerusername ,(const char*)sqlite3_column_text(stmt,0));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return customer;
}

int main(int argc, char* argv[]) {
     if (argc != 2) {
        fprintf(stderr, "Usage: %s <customerusername>\n", argv[0]);
        return 1;
    }

    struct Customer customer = get_customer(argv[1]);
     if (strlen(customer.customerusername)>0) {
        printf("%s\n", customer.customerusername);
    }

}