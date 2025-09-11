#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

typedef struct {
    char username[50];
    char name[100];
    char email[100];
    char phone[20];
} Customer;

Customer getCustomerInfo(const char *customerusername) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    Customer customer = {"", "", "", ""};
    
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return customer;
    }
    
    const char *sql = "SELECT * FROM customer WHERE customerusername = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement\n");
        sqlite3_close(db);
        return customer;
    }
    
    sqlite3_bind_text(stmt, 1, customerusername, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(customer.username, (const char*)sqlite3_column_text(stmt, 0));
        strcpy(customer.name, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(customer.email, (const char*)sqlite3_column_text(stmt, 2));
        strcpy(customer.phone, (const char*)sqlite3_column_text(stmt, 3));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return customer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./Task67 <customerusername>\n");
        return 1;
    }
    
    const char *customerusername = argv[1];
    Customer customer = getCustomerInfo(customerusername);
    
    if (strlen(customer.username) > 0) {
        printf("Customer{username='%s', name='%s', email='%s', phone='%s'}\n",
               customer.username, customer.name, customer.email, customer.phone);
    } else {
        printf("Customer not found.\n");
    }
    
    return 0;
}