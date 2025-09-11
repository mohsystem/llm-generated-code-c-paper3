
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validate_pin(const char *pin) {
    if (!pin) {
        return false;
    }
    
    size_t len = strlen(pin);
    if (len != 4 && len != 6) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit(pin[i])) {
            return false;
        }
    }
    
    return true;
}

int main() {
    // Test cases
    printf("%d\\n", validate_pin("1234"));    // 1 
    printf("%d\\n", validate_pin("12345"));   // 0
    printf("%d\\n", validate_pin("a234"));    // 0
    printf("%d\\n", validate_pin(""));        // 0
    printf("%d\\n", validate_pin("123456"));  // 1
    return 0;
}
