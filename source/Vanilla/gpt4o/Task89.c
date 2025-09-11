#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePasswords(const char* filePath, const char* userInput) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        return false;
    }

    char filePassword[100];
    if (fgets(filePassword, sizeof(filePassword), file) == NULL) {
        fclose(file);
        return false;
    }
    fclose(file);

    // Remove newline character from filePassword if present
    size_t len = strlen(filePassword);
    if (len > 0 && filePassword[len - 1] == '\n') {
        filePassword[len - 1] = '\0';
    }

    if (strlen(filePassword) != strlen(userInput)) {
        return false;
    }

    for (size_t i = 0; i < strlen(userInput); ++i) {
        if (userInput[i] != filePassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("%d\n", comparePasswords("password.txt", "password123")); // 0
    printf("%d\n", comparePasswords("password.txt", "password"));    // 1
    printf("%d\n", comparePasswords("password.txt", "passw0rd"));    // 0
    printf("%d\n", comparePasswords("password.txt", "password!"));   // 0
    printf("%d\n", comparePasswords("password.txt", ""));            // 0
    return 0;
}