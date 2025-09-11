#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isValidPIN(const char* pin) {
    size_t length = strlen(pin);
    if (length != 4 && length != 6) return false;
    for (size_t i = 0; i < length; i++) {
        if (!isdigit(pin[i])) return false;
    }
    return true;
}

int main() {
    printf("%d\n", isValidPIN("1234"));   // 1 (true)
    printf("%d\n", isValidPIN("12345"));  // 0 (false)
    printf("%d\n", isValidPIN("a234"));   // 0 (false)
    printf("%d\n", isValidPIN("123456")); // 1 (true)
    printf("%d\n", isValidPIN("12a4"));   // 0 (false)
    return 0;
}