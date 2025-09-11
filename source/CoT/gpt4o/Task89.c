#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePassword(const char *filePath, const char *inputPassword) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }
    char storedPassword[256];
    if (!fgets(storedPassword, sizeof(storedPassword), file)) {
        fclose(file);
        return false;
    }
    fclose(file);
    size_t len = strlen(storedPassword);
    if (storedPassword[len - 1] == '\n') {
        storedPassword[len - 1] = '\0';
    }
    if (strlen(storedPassword) != strlen(inputPassword)) {
        return false;
    }
    return strcmp(storedPassword, inputPassword) == 0;
}

int main() {
    printf("%d\n", comparePassword("password.txt", "userInput1")); // Example output
    printf("%d\n", comparePassword("password.txt", "userInput2")); // Example output
    printf("%d\n", comparePassword("password.txt", "userInput3")); // Example output
    printf("%d\n", comparePassword("password.txt", "userInput4")); // Example output
    printf("%d\n", comparePassword("password.txt", "userInput5")); // Example output
    return 0;
}