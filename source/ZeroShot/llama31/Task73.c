#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_uppercase(const char* password) {
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            return true;
        }
    }
    return false;
}

bool has_lowercase(const char* password) {
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] >= 'a' && password[i] <= 'z') {
            return true;
        }
    }
    return false;
}

bool has_digit(const char* password) {
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] >= '0' && password[i] <= '9') {
            return true;
        }
    }
    return false;
}

bool has_special_character(const char* password) {
    const char* special_chars = "!@#$%^&*()_+={};':\"|,.<>/?";
    for (int i = 0; i < strlen(password); i++) {
        for (int j = 0; j < strlen(special_chars); j++) {
            if (password[i] == special_chars[j]) {
                return true;
            }
        }
    }
    return false;
}

bool is_valid_password(const char* password) {
    // Check for minimum length of 8 characters
    if (strlen(password) < 8) {
        return false;
    }
    // Check for at least one uppercase letter, one lowercase letter, one digit, and one special character
    if (!has_uppercase(password) || !has_lowercase(password) || !has_digit(password) || !has_special_character(password)) {
        return false;
    }
    return true;
}

int main() {
    const char* testCases[] = {"Password123!", "password123", "Password123", "P@ssw0rd", "short"};
    for (int i = 0; i < 5; i++) {
        printf("Password: %s - Valid: %s\n", testCases[i], is_valid_password(testCases[i]) ? "true" : "false");
    }
    return 0;
}