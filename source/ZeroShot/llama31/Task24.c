#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool validatePIN(const char* pin) {
    int length = strlen(pin);
    if (length == 4 || length == 6) {
        for (int i = 0; i < length; i++) {
            if (!isdigit(pin[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int main() {
    printf("%d\n", validatePIN("1234"));   // 1 (true)
    printf("%d\n", validatePIN("12345")); // 0 (false)
    printf("%d\n", validatePIN("a234"));  // 0 (false)
    printf("%d\n", validatePIN("123456")); // 1 (true)
    printf("%d\n", validatePIN("1234a"));  // 0 (false)
    return 0;
}