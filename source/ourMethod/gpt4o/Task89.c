#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePasswords(const char *filePath, const char *inputPassword) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return false;
    }

    char storedPassword[256];
    if (fgets(storedPassword, sizeof(storedPassword), file) == NULL) {
        fclose(file);
        return false;
    }
    fclose(file);

    // Remove trailing newline character if it exists
    size_t len = strlen(storedPassword);
    if (len > 0 && storedPassword[len - 1] == '\n') {
        storedPassword[len - 1] = '\0';
    }

    if (strlen(storedPassword) != strlen(inputPassword)) {
        return false;
    }

    for (size_t i = 0; i < strlen(storedPassword); i++) {
        if (storedPassword[i] != inputPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("%d\n", comparePasswords("password.txt", "password1"));
    printf("%d\n", comparePasswords("password.txt", "password2"));
    printf("%d\n", comparePasswords("password.txt", "password3"));
    printf("%d\n", comparePasswords("password.txt", "password4"));
    printf("%d\n", comparePasswords("password.txt", "password5"));
    return 0;
}