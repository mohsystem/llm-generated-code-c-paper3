#include <stdio.h>
#include <string.h>

int isPasswordMatch(const char* storedPassword, const char* userInput) {
    if (strlen(storedPassword) != strlen(userInput)) {
        return 0;
    }

    for (size_t i = 0; i < strlen(storedPassword); i++) {
        if (storedPassword[i] != userInput[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char userInput[100];
    printf("Enter the password: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = '\0'; // Remove trailing newline character

    FILE* file = fopen("password.txt", "r");
    if (file != NULL) {
        char storedPassword[100];
        fgets(storedPassword, sizeof(storedPassword), file);
        storedPassword[strcspn(storedPassword, "\n")] = '\0'; // Remove trailing newline character
        fclose(file);

        if (isPasswordMatch(storedPassword, userInput)) {
            printf("Password is correct.\n");
        } else {
            printf("Password is incorrect.\n");
        }
    } else {
        printf("Error reading the password file.\n");
    }

    return 0;
}