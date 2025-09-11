#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validatePin(const char* pin) {
    int length = strlen(pin);
    if (length != 4 && length != 6) return 0;
    for (int i = 0; i < length; i++) {
        if (!isdigit(pin[i])) return 0;
    }
    return 1;
}

int main() {
    printf("%d\n", validatePin("1234"));   // 1 (true)
    printf("%d\n", validatePin("12345"));  // 0 (false)
    printf("%d\n", validatePin("a234"));   // 0 (false)
    printf("%d\n", validatePin("123456")); // 1 (true)
    printf("%d\n", validatePin("0000"));   // 1 (true)
    return 0;
}