#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validatePin(const char *pin) {
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
    printf("%d\n", validatePin("1234"));
    printf("%d\n", validatePin("12345"));
    printf("%d\n", validatePin("a234"));
    printf("%d\n", validatePin("123456"));
    printf("%d\n", validatePin("123a"));
    return 0;
}