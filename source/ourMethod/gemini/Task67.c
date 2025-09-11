#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Structure to hold customer information
typedef struct {
    char customerUsername[255];
    char customerName[255];
    // ... other customer attributes
} Customer;

// Function to retrieve customer information
Customer getCustomerInfo(const char* customerUsername) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    Customer customer = {0}; // Initialize the struct to zero

    int rc = sqlite3_open("your_database.db", &db); // Replace with your database file
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return customer; // Return empty customer object on error
    }

    // Prepare statement with parameter binding to prevent SQL injection
    char* sql = "SELECT * FROM customer WHERE customerusername = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); 
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return customer;  // Return empty customer object on error
    }

    rc = sqlite3_bind_text(stmt, 1, customerUsername, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return customer;  // Return empty customer object on error
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        strcpy(customer.customerUsername, (const char*)sqlite3_column_text(stmt, 0));
        strcpy(customer.customerName, (const char*)sqlite3_column_text(stmt, 1));
        // Retrieve other attributes
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return customer;
}


int main() {
    const char* usernames[] = {"testuser1", "testuser2", "invaliduser", "anotheruser", "testuser3"};
    int num_usernames = sizeof(usernames) / sizeof(usernames[0]);

    for (int i = 0; i < num_usernames; i++) {
        Customer customer = getCustomerInfo(usernames[i]);
        if (strlen(customer.customerUsername) > 0) {
            printf("Customer Information for %s:\n", usernames[i]);
            printf("Username: %s, Name: %s\n", customer.customerUsername, customer.customerName);
            // ... print other customer attributes
        } else {
            printf("Customer not found for username: %s\n", usernames[i]);
        }
        printf("\n");
    }

    return 0;
}