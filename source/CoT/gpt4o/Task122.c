#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

typedef struct User {
    char username[50];
    char passwordHash[65];
    struct User* next;
} User;

User* userDatabase = NULL;

void hashPassword(const char* password, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

int signup(const char* username, const char* password) {
    User* current = userDatabase;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return 0; // User already exists
        }
        current = current->next;
    }

    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    hashPassword(password, newUser->passwordHash);
    newUser->next = userDatabase;
    userDatabase = newUser;
    return 1;
}

void freeDatabase() {
    User* current = userDatabase;
    while (current != NULL) {
        User* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    printf("%d\n", signup("user1", "password1")); // 1
    printf("%d\n", signup("user1", "password2")); // 0
    printf("%d\n", signup("user2", "password3")); // 1
    printf("%d\n", signup("user3", "password4")); // 1
    printf("%d\n", signup("user2", "password5")); // 0

    freeDatabase();
    return 0;
}