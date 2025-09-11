#include <stdio.h>
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
        fprintf(stderr, "File not found\n");
        return NULL;
    }
    char password[1024];
    if (fgets(password, sizeof(password), file) == NULL) {
        fclose(file);
        return NULL;
    }
    password[strcspn(password, "\n")] = 0; // Remove newline character
    fclose(file);
    return strdup(password); // Note: This allocates memory, so it should be freed later
}

int main() {
    const char* filename = "password.txt";
    char* storedPassword = readPasswordFromFile(filename);
    if (storedPassword != NULL) {
        printf("Enter your password: ");
        char userInput[1024];
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = 0; // Remove newline character
        if (comparePasswords(storedPassword, userInput)) {
            printf("Access granted\n");
        } else {
            printf("Access denied\n");
        }
        free(storedPassword); // Free allocated memory
    }
    return 0;
}