#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
}

void registerUser(char* username, char* password, char** users, int* userCount) {
    for (int i = 0; i < *userCount; ++i) {
        if (strcmp(username, users[i]) == 0) {
            printf("Username already exists.\n");
            return;
        }
    }
    users[*userCount] = username;
    char hashedPassword[65];
    hashPassword(password, hashedPassword);
    users[*userCount + 1] = hashedPassword;
    (*userCount) += 2;
    printf("User registered successfully.\n");
}

bool loginUser(char* username, char* password, char** users, int userCount) {
    for (int i = 0; i < userCount; i += 2) {
        if (strcmp(username, users[i]) == 0) {
            char hashedPassword[65];
            hashPassword(password, hashedPassword);
            if (strcmp(hashedPassword, users[i + 1]) == 0) {
                printf("Login successful.\n");
                return true;
            } else {
                printf("Invalid username or password.\n");
                return false;
            }
        }
    }
    printf("Invalid username or password.\n");
    return false;
}

int main() {
    char** users = (char**)malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; ++i) {
        users[i] = (char*)malloc(100 * sizeof(char));
    }
    int userCount = 0;

    while (true) {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        int option;
        scanf("%d", &option);

        if (option == 1) {
            char username[100], password[100];
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            registerUser(username, password, users, &userCount);
        } else if (option == 2) {
            char username[100], password[100];
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            loginUser(username, password, users, userCount);
        } else if (option == 3) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}