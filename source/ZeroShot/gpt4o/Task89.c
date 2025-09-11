#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePasswords(const char* storedPasswordFile, const char* enteredPassword) {
    FILE *file = fopen(storedPasswordFile, "r");
    if (file == NULL) {
        perror("Failed to open the file");
        return false;
    }

    char storedPassword[256];
    if (fgets(storedPassword, sizeof(storedPassword), file) == NULL) {
        fclose(file);
        return false;
    }
    fclose(file);

    storedPassword[strcspn(storedPassword, "\n")] = 0; // Remove newline character

    if (strlen(storedPassword) != strlen(enteredPassword)) return false;
    for (size_t i = 0; i < strlen(storedPassword); ++i) {
        if (storedPassword[i] != enteredPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // Test cases
    printf("%d\n", comparePasswords("password.txt", "password1")); // 0 (false)
    printf("%d\n", comparePasswords("password.txt", "password123")); // 0 (false)
    printf("%d\n", comparePasswords("password.txt", "password")); // 1 (true)
    printf("%d\n", comparePasswords("password.txt", "Password")); // 0 (false)
    printf("%d\n", comparePasswords("password.txt", "passw0rd")); // 0 (false)
    return 0;
}