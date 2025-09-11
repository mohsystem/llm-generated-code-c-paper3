// Highly conceptual example. In practice, you would use libraries like libcurl for HTTP and SQLite for the database.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP request handler
void handle_request(char* name, char* email) {
    // Mock database insertion
    printf("Inserting user %s with email %s into database\n", name, email);
}

int main() {
    char* test_cases[][2] = {
        {"John Doe", "john@example.com"},
        {"Jane Doe", "jane@example.com"},
        {"Alice Smith", "alice@example.com"},
        {"Bob Johnson", "bob@example.com"},
        {"Charlie Brown", "charlie@example.com"}
    };

    for (int i = 0; i < 5; i++) {
        handle_request(test_cases[i][0], test_cases[i][1]);
    }

    return 0;
}