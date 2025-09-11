#include <stdio.h>
#include <string.h>
#include <sqlite3.h> // Or your preferred database library


struct Customer {
    int id;
    char customerusername[255];
    char name[255];
    char email[255];
};


struct Customer* getCustomer(const char* customerUsername) {
    sqlite3* db;
    char* errmsg = 0;
    int rc = sqlite3_open("your_database.db", &db); // Replace with your database file

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    char sql[512]; // Make sure it's large enough
    snprintf(sql, sizeof(sql), "SELECT * FROM customer WHERE customerusername = '%s'", customerUsername);

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    struct Customer* customer = NULL;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        customer = (struct Customer*)malloc(sizeof(struct Customer));
        if (customer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return NULL;
        }
        customer->id = sqlite3_column_int(stmt, 0);
        strcpy(customer->customerusername, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        strcpy(customer->name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        strcpy(customer->email, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))); // Adjust column indices
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return customer;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a customer username as a command-line argument.\n");
        return 1;
    }


    struct Customer* customer = getCustomer(argv[1]);

    if (customer) {
        printf("ID: %d\n", customer->id);
        printf("Username: %s\n", customer->customerusername);
        printf("Name: %s\n", customer->name);
        printf("Email: %s\n", customer->email);
        free(customer); // Free allocated memory
    } else {
        printf("Customer not found.\n");
    }

    return 0;
}