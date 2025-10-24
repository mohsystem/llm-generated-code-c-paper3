#include <stdio.h>
#include <stdbool.h>

bool is_isogram(const char* s) {
    if (s == NULL) {
        return false; // fail closed
    }
    bool seen[26] = { false };
    for (size_t i = 0; s[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)s[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = (unsigned char)(ch + ('a' - 'A'));
        } else if (!(ch >= 'a' && ch <= 'z')) {
            return false; // invalid character
        }
        int idx = (int)(ch - 'a');
        if (seen[idx]) {
            return false;
        }
        seen[idx] = true;
    }
    return true;
}

int main(void) {
    const char* tests[] = {
        "Dermatoglyphics",
        "aba",
        "moOse",
        "",
        "isogram"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < count; i++) {
        printf("\"%s\" -> %s\n", tests[i], is_isogram(tests[i]) ? "true" : "false");
    }
    return 0;
}