#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparePassword(const char* filePath, const char* inputPassword) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char storedPassword[100];
    fgets(storedPassword, sizeof(storedPassword), file);
    fclose(file);

    // Remove trailing newline character from storedPassword
    storedPassword[strcspn(storedPassword, "\n")] = '\0';

    if (strlen(storedPassword) != strlen(inputPassword)) {
        return 0;
    }

    for (size_t i = 0; i < strlen(storedPassword); i++) {
        if (storedPassword[i] != inputPassword[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    const char* filePath = "password.txt";
    const char* testCases[5] = {"password123", "wrongPassword", "p@ssw0rd", "pass123", "pass"};

    for (size_t i = 0; i < 5; i++) {
        printf("Input Password: %s\n", testCases[i]);
        printf("Match: %s\n\n", comparePassword(filePath, testCases[i]) ? "true" : "false");
    }

    return 0;
}