#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool validate_pin(const char *pin) {
    int len = strlen(pin);
    if (len != 4 && len != 6)
        return false;
    for (int i = 0; i < len; i++)
        if (pin[i] < '0' || pin[i] > '9')
            return false;
    return true;
}

int main() {
    printf("%d\n", validate_pin("1234")); // 1 (true)
    printf("%d\n", validate_pin("12345")); // 0 (false)
    printf("%d\n", validate_pin("a234")); // 0 (false)
    return 0;
}