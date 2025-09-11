
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PASSWORD_LENGTH 100

char* read_password_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\\n");
        return NULL;
    }

    char* password = (char*)malloc(MAX_PASSWORD_LENGTH);
    if (password == NULL) {
        fclose(file);
        return NULL;
    }

    if (fgets(password, MAX_PASSWORD_LENGTH, file) == NULL) {
        free(password);
        fclose(file);
        return NULL;
    }

    // Remove newline if present
    password[strcspn(password, "\\n")] = 0;
    fclose(file);
    return password;
}

bool compare_passwords(const char* stored_pass, const char* user_pass) {
    if (stored_pass == NULL || user_pass == NULL) {
        return false;
    }
    
    if (strlen(stored_pass) != strlen(user_pass)) {
        return false;
    }

    bool result = true;
    for (size_t i = 0; i < strlen(stored_pass); i++) {
        if (stored_pass[i] != user_pass[i]) {
            result = false;
        }
    }
    return result;
}

int main() {
    const char* test_inputs[] = {
        "password123",
        "wrongpass",
        "correctpass",
        "test1234",
        "securepass"
    };
    
    // Create test file with stored password
    FILE* file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("Error creating test file\\n");
        return 1;
    }
    fprintf(file, "correctpass");
    fclose(file);

    for (int i = 0; i < 5; i++) {
        char* stored_password = read_password_from_file("password.txt");
        if (stored_password != NULL) {
            bool match = compare_passwords(stored_password, test_inputs[i]);
            printf("Test password: %s - Match: %s\\n", test_inputs[i], match ? "true" : "false");
            free(stored_password);
        }
    }

    return 0;
}
