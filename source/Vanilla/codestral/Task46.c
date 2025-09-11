#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    char name[50];
    char email[50];
    char password[50];
} User;

typedef struct Task46 {
    User users[100]; // Assuming a maximum of 100 users
    int count;
} Task46;

void registerUser(Task46* system, const char* name, const char* email, const char* password) {
    User user;
    strcpy(user.name, name);
    strcpy(user.email, email);
    strcpy(user.password, password);
    system->users[system->count++] = user;
}

int main() {
    Task46 system;
    system.count = 0;
    registerUser(&system, "John Doe", "johndoe@example.com", "password123");
    registerUser(&system, "Jane Doe", "janedoe@example.com", "securepassword");
    // Add more test cases here

    return 0;
}