
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PASSWORD_LENGTH 100

bool comparePassword(const char* storedPass, const char* inputPass) {
    if (storedPass == NULL || inputPass == NULL) {
        return false;
    }
    
    if (strlen(storedPass) != strlen(inputPass)) {
        return false;
    }
    
    bool result = true;
    for (size_t i = 0; i < strlen(storedPass); i++) {
        result &= (storedPass[i] == inputPass[i]);
    }
    return result;
}

int main() {
    char storedPassword[MAX_PASSWORD_LENGTH];
    FILE* file = fopen("password.txt", "r");
    
    if (file == NULL) {
        fprintf(stderr, "Error opening password file\\n");
        return 1;
    }
    
    if (fgets(storedPassword, MAX_PASSWORD_LENGTH, file) == NULL) {
        fprintf(stderr, "Error reading password file\\n");
        fclose(file);
        return 1;
    }
    
    // Remove newline if present
    storedPassword[strcspn(storedPassword, "\\n")] = 0;
    fclose(file);
    
    // Test case 1: Correct password
    printf("%d\\n", comparePassword(storedPassword, storedPassword));
    
    // Test case 2: Wrong password
    printf("%d\\n", comparePassword(storedPassword, "wrongpass"));
    
    // Test case 3: Empty password
    printf("%d\\n", comparePassword(storedPassword, ""));
    
    // Test case 4: NULL password
    printf("%d\\n", comparePassword(storedPassword, NULL));
    
    // Test case 5: Same length but different characters
    char sameLength[MAX_PASSWORD_LENGTH];
    memset(sameLength, 'X', strlen(storedPassword));
    sameLength[strlen(storedPassword)] = '\\0';
    printf("%d\\n", comparePassword(storedPassword, sameLength));
    
    return 0;
}
