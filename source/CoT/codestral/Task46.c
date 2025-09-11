/* This example assumes that the maximum number of users is 100.
   In a real-world application, you would need to dynamically allocate memory
   for the users or use a data structure that can grow as needed. */

#include <string.h>

typedef struct {
    char name[100];
    char email[100];
    char password[100];
} User;

User users[100];
int userCount = 0;

void registerUser(char *name, char *email, char *password) {
    strcpy(users[userCount].name, name);
    strcpy(users[userCount].email, email);
    strcpy(users[userCount].password, password);
    userCount++;
}

int main() {
    registerUser("John Doe", "john.doe@example.com", "password123");
    return 0;
}