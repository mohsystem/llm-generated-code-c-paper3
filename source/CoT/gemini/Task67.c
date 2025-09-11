//  C version is very similar to C++ version. 
//  You would need to use a C database library (like sqlite3) and handle strings differently (char arrays instead of std::string).
//  The overall logic and security considerations remain the same.


#include <stdio.h>
#include <string.h>
#include <sqlite3.h> // Use SQLite for demonstration


struct Customer {
    int id;
    char customerUsername[256]; // Use a fixed-size array or dynamic allocation
    char name[256];
    char email[256];
};

Customer* get_customer(const char* customer_username, const char* db_path) {
    // ... (Implementation very similar to C++ version, 
    // but using C string functions and sqlite3 C API) ...
     sqlite3* db;
    int rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_stmt* stmt;
    char* sql = "SELECT * FROM customer WHERE customerusername = ?"; 
    // or use sqlite3_snprintf to dynamically build the query

    // ... (rest of the database interaction logic is similar to C++ version)

    return NULL; // Replace with actual return logic
}


int main(int argc, char* argv[]) {
     if (argc < 2) {
        fprintf(stderr, "Please provide a customer username as a command-line argument.\n");
        return 1;
    }

    // Example with in-memory database (replace with your actual DB path)
    const char* db_path = ":memory:";
    sqlite3* db;
    int rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char* errmsg;
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS customer (id INTEGER PRIMARY KEY, customerusername TEXT UNIQUE, name TEXT, email TEXT)", NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Create table error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, "INSERT OR IGNORE INTO customer VALUES (1, 'testuser1', 'Test User 1', 'test1@example.com'), (2, 'testuser2', 'Test User 2', 'test2@example.com')", NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert data error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);




    char* customer_username = argv[1];
    Customer* customer = get_customer(customer_username, db_path);
     if (customer) {
        printf("ID: %d\n", customer->id);
        // ... (Print other customer details) ...
        free(customer); // Free the allocated memory!

    } else {
        printf("Customer not found.\n");
    }



    return 0;
}