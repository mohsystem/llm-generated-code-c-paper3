// C code for a simple API endpoint using a local list as a mock database

#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_LENGTH 256

char database[MAX_USERS][MAX_LENGTH];
int user_count = 0;

const char* addUser(const char* userData) {
    if (userData == NULL || strlen(userData) == 0) {
        return "Invalid user data.";
    }
    if (user_count < MAX_USERS) {
        strncpy(database[user_count], userData, MAX_LENGTH - 1);
        database[user_count][MAX_LENGTH - 1] = '\0';
        user_count++;
        return "User added successfully.";
    }
    return "Database is full.";
}

int main() {
    printf("%s\n", addUser("John Doe"));
    printf("%s\n", addUser("Jane Smith"));
    printf("%s\n", addUser(""));
    printf("%s\n", addUser(NULL));
    printf("%s\n", addUser("Alice Brown"));
    return 0;
}