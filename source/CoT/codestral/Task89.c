#include <stdio.h>
#include <string.h>

int comparePasswords(const char* inputPassword) {
    FILE* file = fopen("password.txt", "r");
    char storedPassword[100];
    fgets(storedPassword, 100, file);
    fclose(file);

    if (strlen(inputPassword) != strlen(storedPassword)) {
        return 0;
    }

    for (size_t i = 0; i < strlen(inputPassword); i++) {
        if (inputPassword[i] != storedPassword[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char inputPassword[100];
    printf("Enter your password: ");
    fgets(inputPassword, 100, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0;

    if (comparePasswords(inputPassword)) {
        printf("Password is correct.\n");
    } else {
        printf("Password is incorrect.\n");
    }

    return 0;
}