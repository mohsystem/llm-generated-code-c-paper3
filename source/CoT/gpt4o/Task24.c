#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isValidPIN(const char *pin) {
    if (pin == NULL) {
        return false;
    }
    int length = strlen(pin);
    if (length != 4 && length != 6) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        if (!isdigit(pin[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("%s\n", isValidPIN("1234") ? "true" : "false");   // true
    printf("%s\n", isValidPIN("12345") ? "true" : "false");  // false
    printf("%s\n", isValidPIN("a234") ? "true" : "false");   // false
    printf("%s\n", isValidPIN("123456") ? "true" : "false"); // true
    printf("%s\n", isValidPIN("12b456") ? "true" : "false"); // false
    return 0;
}