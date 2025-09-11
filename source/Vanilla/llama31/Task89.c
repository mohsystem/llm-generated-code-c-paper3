#include <stdio.h>
#include <string.h>

int comparePasswords(const char* storedPassword, const char* userInput) {
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
    const char* storedPassword = "historia";
    const char* testCases[] = {"historia", "history", "histo", "historias", "other"};
    for (size_t i = 0; i < 5; i++) {
        printf("Password: %s - %s\n", testCases[i], comparePasswords(storedPassword, testCases[i]) ? "Valid" : "Invalid");
    }
    return 0;
}