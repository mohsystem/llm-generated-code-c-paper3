#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool comparePasswords(const char* storedPassword, const char* userInput) {
    if (strlen(storedPassword) != strlen(userInput)) {
        return false;
    }
    for (size_t i = 0; i < strlen(storedPassword); ++i) {
        if (storedPassword[i] != userInput[i]) {
            return false;
        }
    }
    return true;
}

char* readPasswordFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return NULL;
    }
    char* password = (char*)malloc(1024 * sizeof(char));
    if (fgets(password, 1024, file) == NULL) {
        free(password);
        fclose(file);
        return NULL;
    }
    password[strcspn(password, "\n")] = 0; // Remove newline character
    fclose(file);
    return password;
}

int main() {
    const char* filename = "password.txt";
    char* storedPassword = readPasswordFromFile(filename);
    if (storedPassword != NULL) {
        printf("Enter your password: ");
        char userInput[1024];
        fgets(userInput, 1024, stdin);
        userInput[strcspn(userInput, "\n")] = 0; // Remove newline character
        if (comparePasswords(storedPassword, userInput)) {
            printf("Passwords match.\n");
        } else {
            printf("Passwords do not match.\n");
        }
        free(storedPassword);
    }
    return 0;
}