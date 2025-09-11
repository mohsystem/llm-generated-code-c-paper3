#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    char name[100];
    char email[100];
    char password[100];
} User;

typedef struct Database {
    User* users;
    int size;
    int capacity;
} Database;

void initDatabase(Database* db) {
    db->users = NULL;
    db->size = 0;
    db->capacity = 0;
}

void registerUser(Database* db, const char* name, const char* email, const char* password) {
    for (int i = 0; i < db->size; ++i) {
        if (strcmp(db->users[i].name, name) == 0) {
            printf("Username already exists.\n");
            return;
        }
    }

    if (db->size == db->capacity) {
        db->capacity += 10;
        db->users = realloc(db->users, db->capacity * sizeof(User));
    }

    strcpy(db->users[db->size].name, name);
    strcpy(db->users[db->size].email, email);
    strcpy(db->users[db->size].password, password);
    db->size++;

    printf("Registration successful.\n");
}

void loginUser(const Database* db, const char* name, const char* password) {
    for (int i = 0; i < db->size; ++i) {
        if (strcmp(db->users[i].name, name) == 0 && strcmp(db->users[i].password, password) == 0) {
            printf("Login successful.\n");
            return;
        }
    }

    printf("Invalid username or password.\n");
}

int main() {
    Database db;
    initDatabase(&db);

    // Test cases
    registerUser(&db, "user1", "user1@example.com", "password1");
    registerUser(&db, "user2", "user2@example.com", "password2");
    registerUser(&db, "user3", "user3@example.com", "password3");
    loginUser(&db, "user1", "password1");
    loginUser(&db, "user2", "wrongpassword");

    free(db.users);
    return 0;
}