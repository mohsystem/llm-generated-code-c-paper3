
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparePassword(const char* storedPass, const char* enteredPass) {
    if (strlen(storedPass) != strlen(enteredPass)) {
        return false;
    }
    
    for (size_t i = 0; i < strlen(storedPass); i++) {
        if (storedPass[i] != enteredPass[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const char* storedPasswords[] = {
        "password123",
        "abc123",
        "test@123",
        "",
        "Pass Word"
    };
    
    const char* enteredPasswords[] = {
        "password123", // true
        "abc124", // false
        "test@12", // false
        "", // true
        "Pass word" // false
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Test Case %d: %s\\n", i+1, 
            comparePassword(storedPasswords[i], enteredPasswords[i]) ? "true" : "false");
    }
    
    return 0;
}
