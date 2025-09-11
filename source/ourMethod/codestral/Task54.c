#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define PASSWORD_LENGTH 6

char* generatePassword() {
    char* password = malloc(PASSWORD_LENGTH + 1);
    srand(time(0));
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        password[i] = '0' + rand() % 10;
    }
    password[PASSWORD_LENGTH] = '\0';
    return password;
}

bool verifyPassword(const char* userInput, const char* generatedPassword) {
    return strcmp(userInput, generatedPassword) == 0;
}

int main() {
    char* generatedPassword = generatePassword();
    printf("Generated password: %s\n", generatedPassword);
    const char* userInput = "input from user";
    if (verifyPassword(userInput, generatedPassword)) {
        printf("Login successful\n");
    } else {
        printf("Login failed\n");
    }
    free(generatedPassword);
    return 0;
}