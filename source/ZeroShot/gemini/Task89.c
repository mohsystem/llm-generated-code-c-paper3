#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_PASSWORD_LENGTH 256

bool comparePasswords(const char* storedPassword, const char* enteredPassword) {
    unsigned char storedPasswordHash[SHA256_DIGEST_LENGTH];
    unsigned char enteredPasswordHash[SHA256_DIGEST_LENGTH];

    SHA256((const unsigned char*)storedPassword, strlen(storedPassword), storedPasswordHash);
    SHA256((const unsigned char*)enteredPassword, strlen(enteredPassword), enteredPasswordHash);

    return memcmp(storedPasswordHash, enteredPasswordHash, SHA256_DIGEST_LENGTH) == 0;
}

char* readPasswordFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Password file not found.\n");
        return NULL;
    }

    char* password = (char*)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
    if (fgets(password, MAX_PASSWORD_LENGTH, file) == NULL) {
        fclose(file);
        free(password);
        return NULL;
    }
    fclose(file);

    // Remove trailing newline character if present
    size_t len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }
    return password;
}


int main() {
    char* storedPassword = readPasswordFromFile("password.txt");
    if (storedPassword == NULL) {
        return 1;
    }

    char enteredPassword[MAX_PASSWORD_LENGTH];
    printf("Enter password: ");
    if (fgets(enteredPassword, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        free(storedPassword);
        return 1;
    }

    // Remove trailing newline character if present
    size_t len = strlen(enteredPassword);
    if (len > 0 && enteredPassword[len - 1] == '\n') {
        enteredPassword[len - 1] = '\0';
    }



    if (comparePasswords(storedPassword, enteredPassword)) {
        printf("Password verified.\n");
    } else {
        printf("Incorrect password.\n");
    }

    free(storedPassword);

    return 0;
}