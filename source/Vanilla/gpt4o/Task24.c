#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidPin(const char *pin) {
    int len = strlen(pin);
    if (len != 4 && len != 6) {
        return 0;
    }
    for (int i = 0; i < len; ++i) {
        if (!isdigit(pin[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    printf("%d\n", isValidPin("1234"));  // true
    printf("%d\n", isValidPin("12345")); // false
    printf("%d\n", isValidPin("a234"));  // false
    printf("%d\n", isValidPin("123456")); // true
    printf("%d\n", isValidPin("123a"));  // false
    return 0;
}