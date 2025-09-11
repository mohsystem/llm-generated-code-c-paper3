#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePasswords(const char *storedPassword, const char *enteredPassword) {
    if (strlen(storedPassword) != strlen(enteredPassword)) {
        return false;
    }
    for (int i = 0; storedPassword[i] != '\0'; i++) {
        if (storedPassword[i] != enteredPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    FILE *file = fopen("password.txt", "r");
    char storedPassword[256];
    fgets(storedPassword, sizeof(storedPassword), file);

    // Remove trailing newline if present
    size_t len = strlen(storedPassword);
    if (len > 0 && storedPassword[len - 1] == '\n') {
        storedPassword[len - 1] = '\0';
    }

    fclose(file);


    printf("%s\n", comparePasswords(storedPassword, "password123") ? "true" : "false");
    printf("%s\n", comparePasswords(storedPassword, "passwor123") ? "true" : "false");
    printf("%s\n", comparePasswords(storedPassword, "password1234") ? "true" : "false");
    printf("%s\n", comparePasswords(storedPassword, "pa55word123") ? "true" : "false");
    printf("%s\n", comparePasswords(storedPassword, storedPassword) ? "true" : "false");


    return 0;
}