#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    char email[100];
    char password[100];
} User;

typedef struct {
    User* users;
    size_t size;
} UserDatabase;

void registerUser(UserDatabase* db, const char* name, const char* email, const char* password) {
    db->users = realloc(db->users, (db->size + 1) * sizeof(User));
    strcpy(db->users[db->size].name, name);
    strcpy(db->users[db->size].email, email);
    strcpy(db->users[db->size].password, password);
    db->size++;
}

void printUsers(const UserDatabase* db) {
    for (size_t i = 0; i < db->size; ++i) {
        printf("Name: %s, Email: %s\n", db->users[i].name, db->users[i].email);
    }
}

int main() {
    UserDatabase db = {NULL, 0};

    // Test cases
    registerUser(&db, "Alice", "alice@example.com", "password123");
    registerUser(&db, "Bob", "bob@example.com", "password456");
    registerUser(&db, "Charlie", "charlie@example.com", "password789");
    registerUser(&db, "David", "david@example.com", "password101112");
    registerUser(&db, "Eve", "eve@example.com", "password131415");

    printUsers(&db);

    free(db.users);
    return 0;
}