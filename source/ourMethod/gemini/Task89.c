#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePasswords(const char* storedPassword, const char* enteredPassword) {
    if (strlen(storedPassword) != strlen(enteredPassword)) {
        return false;
    }
    for (size_t i = 0; i < strlen(storedPassword); ++i) {
        if (storedPassword[i] != enteredPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // Test cases
    printf("Test case 1: %s\n", comparePasswords("password123", "password123") ? "true" : "false"); // Expected: true
    printf("Test case 2: %s\n", comparePasswords("password123", "Password123") ? "true" : "false"); // Expected: false
    printf("Test case 3: %s\n", comparePasswords("password123", "pass") ? "true" : "false"); // Expected: false
    printf("Test case 4: %s\n", comparePasswords("", "") ? "true" : "false"); // Expected: true
    printf("Test case 5: %s\n", comparePasswords("12345", "123456") ? "true" : "false"); // Expected: false

    char storedPasswordFromFile[256];
    FILE *passwordFile = fopen("password_file.txt", "r");

    if (passwordFile == NULL) {
        perror("Unable to open password file");
        return 1;
    }

    if (fgets(storedPasswordFromFile, sizeof(storedPasswordFromFile), passwordFile) != NULL) {
        // Remove trailing newline if present
        storedPasswordFromFile[strcspn(storedPasswordFromFile, "\n")] = 0;
    } else {
        fclose(passwordFile);
        perror("Error reading from file");
        return 1;
    }
    fclose(passwordFile);


    char enteredPassword[256];
    printf("Enter your password: ");

    // Use fgets to prevent potential buffer overflow
    if (fgets(enteredPassword, sizeof(enteredPassword), stdin) != NULL) {
        enteredPassword[strcspn(enteredPassword, "\n")] = 0; // remove the trailing newline character if present
    } else {
        perror("Error reading input");
        return 1;
    }


    if (comparePasswords(storedPasswordFromFile, enteredPassword)) {
        printf("Password verified.\n");
    } else {
        printf("Incorrect password.\n");
    }

    memset(enteredPassword, 0, sizeof(enteredPassword)); // Clear password from memory
    return 0;
}