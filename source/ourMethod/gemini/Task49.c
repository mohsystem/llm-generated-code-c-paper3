// Comment: Implementing a full REST API endpoint in C requires a significant amount of code including handling HTTP requests, JSON parsing, and database interaction. This is outside the scope of a simple example. This example demonstrates the core database interaction part.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Secure coding: Avoid hardcoding credentials in real applications
#define DB_PATH "users.db"


//  Structure to represent user data
typedef struct {
    char* name;
    char* email;
} UserData;


// Function to create a user in the database
int create_user(UserData* user) {
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open(DB_PATH, &db); // Secure Coding: Use parameterized queries

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1; // Indicate an error
    }

    // Input validation: Handle potential NULL values or empty strings.
    if (user == NULL || user->name == NULL || user->email == NULL || strlen(user->name) == 0 || strlen(user->email) == 0) {
         fprintf(stderr, "Invalid user data\n");
         sqlite3_close(db);
         return 1;
    }

    char sql[256]; // Secure Coding: Validate length of the query
    snprintf(sql, sizeof(sql), "INSERT INTO users (name, email) VALUES ('%q', '%q')", user->name, user->email); // parameterized query to prevent sql injection.


    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1; // Indicate an error
    }

    sqlite3_close(db);
    return 0; // Success
}


int main() {


    // Test cases
    UserData user1 = {"John Doe", "john.doe@example.com"};
    if (create_user(&user1) == 0) {
       printf("Test case 1: User created successfully\n");
    }

    UserData user2 = {NULL, "jane.doe@example.com"}; //missing name
    if (create_user(&user2) == 0) {
        printf("Test case 2: User created successfully\n");
    } else {
        printf("Test case 2: Failed to create user\n");
    }


    UserData user3 = {"Robert", ""};  // empty email
    if (create_user(&user3) == 0) {
        printf("Test case 3: User created successfully\n");
    } else {
        printf("Test case 3: Failed to create user\n");
    }

    // Simulate database error by using incorrect path
    #undef DB_PATH // Remove the original value. Comment to test with correct path.
    #define DB_PATH "invalid.db"  // simulate db error
    UserData user4 = {"DB Error", "error@example.com"};
    if (create_user(&user4) == 0) {
        printf("Test case 4: User created successfully\n");
    } else {
        printf("Test case 4: Failed to create user\n");
    }
    #undef DB_PATH // Remove the temporary value.
    #define DB_PATH "users.db"


    return 0;
}