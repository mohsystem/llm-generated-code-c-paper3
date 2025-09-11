#include <stdio.h>
#include <ctype.h>
#include <string.h>

int validatePin(const char* pin) {
    // Check if the length is either 4 or 6
    int length = strlen(pin);
    if (length != 4 && length != 6) {
        return 0;
    }
    
    // Check if all characters are digits
    for (int i = 0; i < length; i++) {
        if (!isdigit(pin[i])) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    const char* testCases[] = {"1234", "12345", "a234", "123456", "abcdef"};
    for (int i = 0; i < 5; i++) {
        printf("%s: %s\n", testCases[i], validatePin(testCases[i]) ? "true" : "false");
    }
    return 0;
}