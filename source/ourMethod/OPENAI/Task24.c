#include <stdio.h>
#include <string.h>

int isValidPIN(const char* pin) {
    if (pin == NULL) {
        return 0;
    }
    size_t n = strlen(pin);
    if (n != 4 && n != 6) {
        return 0;
    }
    for (size_t i = 0; i < n; ++i) {
        char c = pin[i];
        if (c < '0' || c > '9') {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    const char* tests[] = {"1234", "12345", "a234", "0000", "098765"};
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < num_tests; ++i) {
        printf("%s -> %s\n", tests[i], isValidPIN(tests[i]) ? "true" : "false");
    }
    return 0;
}