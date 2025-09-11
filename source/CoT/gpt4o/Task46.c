#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

typedef struct {
    char name[50];
    char email[50];
    char password[50];
} User;

typedef struct {
    User users[100];
    int count;
} Database;

int isValidEmail(const char* email) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (reti) {
        return 0;
    }
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int isValidPassword(const char* password) {
    return strlen(password) >= 8;
}

char* registerUser(const char* name, const char* email, const char* password, Database* db) {
    if (!isValidEmail(email)) {
        return "Invalid email format";
    }
    if (!isValidPassword(password)) {
        return "Password must be at least 8 characters";
    }
    strcpy(db->users[db->count].name, name);
    strcpy(db->users[db->count].email, email);
    strcpy(db->users[db->count].password, password);
    db->count++;
    return "Registration successful";
}

void printUsers(Database* db) {
    printf("Registered Users:\n");
    for (int i = 0; i < db->count; i++) {
        printf("User{name='%s', email='%s'}\n", db->users[i].name, db->users[i].email);
    }
}

int main() {
    Database db;
    db.count = 0;
    printf("%s\n", registerUser("Alice", "alice@example.com", "password123", &db));
    printf("%s\n", registerUser("Bob", "bob_at_example.com", "pass", &db));
    printf("%s\n", registerUser("Charlie", "charlie@example.com", "charlie123", &db));
    printf("%s\n", registerUser("Dave", "dave@example", "davepass", &db));
    printf("%s\n", registerUser("Eve", "eve@example.com", "evepass123", &db));

    printUsers(&db);

    return 0;
}