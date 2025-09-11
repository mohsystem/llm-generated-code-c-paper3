
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PASSWORD_LENGTH 256

// Constant time comparison to prevent timing attacks
static bool compare_passwords(const char* stored_pass, const char* input_pass) {
    size_t stored_len = strlen(stored_pass);
    size_t input_len = strlen(input_pass);
    
    if (stored_len != input_len) {
        return false;
    }
    
    bool result = true;
    for (size_t i = 0; i < stored_len; i++) {
        // Use & instead of && to prevent timing attacks
        result &= (stored_pass[i] == input_pass[i]);
    }
    return result;
}

bool verify_password(const char* filename, const char* input_password) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return false;
    }
    
    char stored_pass[MAX_PASSWORD_LENGTH];
    if (!fgets(stored_pass, sizeof(stored_pass), file)) {
        fclose(file);
        return false;
    }
    
    // Remove newline if present
    size_t len = strlen(stored_pass);
    if (len > 0 && stored_pass[len-1] == '\\n') {
        stored_pass[len-1] = '\\0';
    }
    
    fclose(file);
    return compare_passwords(stored_pass, input_password);
}

int main() {
    const char* test_passwords[] = {
        "correctpass",
        "wrongpass",
        "short",
        "verylongpassword",
        ""
    };
    const int num_tests = 5;
    
    // Create test file with stored password
    FILE* file = fopen("password.txt", "w");
    if (!file) {
        printf("Error creating test file\\n");
        return 1;
    }
    
    fprintf(file, "correctpass");
    fclose(file);
    
    for (int i = 0; i < num_tests; i++) {
        bool result = verify_password("password.txt", test_passwords[i]);
        printf("Password '%s': %s\\n", test_passwords[i], result ? "true" : "false");
    }
    
    // Clean up test file
    remove("password.txt");
    
    return 0;
}
