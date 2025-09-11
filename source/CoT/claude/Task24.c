
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validatePIN(const char* pin) {
    if (pin == NULL) {
        return false;
    }
    
    int len = strlen(pin);
    if (len != 4 && len != 6) {
        return false;
    }
    
    for (int i = 0; i < len; i++) {
        if (!isdigit(pin[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    // Test cases
    printf("%d\\n", validatePIN("1234"));    // 1
    printf("%d\\n", validatePIN("12345"));   // 0
    printf("%d\\n", validatePIN("a234"));    // 0
    printf("%d\\n", validatePIN("123456"));  // 1
    printf("%d\\n", validatePIN(""));        // 0
    return 0;
}
