#include <stdio.h>
#include <string.h>

bool comparePasswords(const char* storedPassword, const char* userInput) {
    if (strlen(storedPassword) != strlen(userInput)) {
        return false;
    }
    for (size_t i = 0; i < strlen(storedPassword); i++) {
        if (storedPassword[i] != userInput[i]) {
            return false;
        }
    }
    return true;
}

char* readPasswordFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File not found.\n");
        return NULL;
    }
    char password[1024];
    fgets(password, sizeof(password), file);
    password[strcspn(password, "\n")] = 0; // Remove newline character
    fclose(file);
    return strdup(password); // Note: This allocates memory and should be freed later
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
            printf("Passwords match.\n");
        } else {
            printf("Passwords do not match.\n");
        }
        free(storedPassword); // Free allocated memory
    }

    // Test cases
    printf("%d\n", comparePasswords("password123", "password123")); // 1 (true)
    printf("%d\n", comparePasswords("password123", "wrongpassword")); // 0 (false)
    printf("%d\n", comparePasswords("password123", "password12")); // 0 (false)
    printf("%d\n", comparePasswords("password123", "password1234")); // 0 (false)
    printf("%d\n", comparePasswords("password123", "Password123")); // 0 (false)

    return 0;
}