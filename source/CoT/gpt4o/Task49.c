// C code to simulate storing user data (e.g., name and email) in a database.
// Due to the complexity of an actual database connection, this code will simulate the storage.
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    char email[100];
} UserData;

UserData database[100];
int dbIndex = 0;

int storeUserData(const char *name, const char *email) {
    if (name == NULL || email == NULL || strlen(name) == 0 || strlen(email) == 0) {
        return 0;
    }
    strcpy(database[dbIndex].name, name);
    strcpy(database[dbIndex].email, email);
    dbIndex++;
    return 1;
}

int main() {
    printf("%d\n", storeUserData("John Doe", "john@example.com"));
    printf("%d\n", storeUserData("Jane Doe", "jane@example.com"));
    printf("%d\n", storeUserData("", "invalid@example.com"));
    printf("%d\n", storeUserData("Invalid User", ""));
    printf("%d\n", storeUserData("Alice", "alice@example.com"));
    return 0;
}