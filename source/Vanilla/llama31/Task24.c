#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isValidPin(const char* pin) {
    int length = strlen(pin);
    if (length != 4 && length != 6) return false;
    for (int i = 0; i < length; i++) {
        if (!isdigit(pin[i])) return false;
    }
    return true;
}

int main() {
    printf("%d\n", isValidPin("1234"));   // 1 (true)
    printf("%d\n", isValidPin("12345"));  // 0 (false)
    printf("%d\n", isValidPin("a234"));   // 0 (false)
    printf("%d\n", isValidPin("123456")); // 1 (true)
    printf("%d\n", isValidPin(""));       // 0 (false)
    return 0;
}