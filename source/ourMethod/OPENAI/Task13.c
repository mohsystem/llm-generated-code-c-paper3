#include <stdio.h>
#include <stdbool.h>

static bool is_valid_dir_char(char c) {
    return c == 'n' || c == 's' || c == 'e' || c == 'w';
}

bool isValidWalk(const char* walk[], int len) {
    if (walk == NULL || len != 10) {
        return false;
    }
    int x = 0;
    int y = 0;
    for (int i = 0; i < len; i++) {
        const char* s = walk[i];
        if (s == NULL) {
            return false;
        }
        /* Ensure exactly one character */
        if (s[0] == '\0' || s[1] != '\0') {
            return false;
        }
        char c = s[0];
        if (!is_valid_dir_char(c)) {
            return false;
        }
        switch (c) {
            case 'n': y += 1; break;
            case 's': y -= 1; break;
            case 'e': x += 1; break;
            case 'w': x -= 1; break;
            default: return false;
        }
    }
    return x == 0 && y == 0;
}

int main(void) {
    const char* t1[] = {"n","s","n","s","n","s","n","s","n","s"}; /* true */
    const char* t2[] = {"w"};                                     /* false (not 10) */
    const char* t3[] = {"n","n","n","s","n","s","n","s","n","s"}; /* false (not back) */
    const char* t4[] = {"e","w","e","w","e","w","e","w","e","w"}; /* true */
    const char* t5[] = {"n","s","x","s","n","s","n","s","n","s"}; /* false (invalid) */

    printf("Test 1: %s\n", isValidWalk(t1, (int)(sizeof(t1)/sizeof(t1[0]))) ? "true" : "false");
    printf("Test 2: %s\n", isValidWalk(t2, (int)(sizeof(t2)/sizeof(t2[0]))) ? "true" : "false");
    printf("Test 3: %s\n", isValidWalk(t3, (int)(sizeof(t3)/sizeof(t3[0]))) ? "true" : "false");
    printf("Test 4: %s\n", isValidWalk(t4, (int)(sizeof(t4)/sizeof(t4[0]))) ? "true" : "false");
    printf("Test 5: %s\n", isValidWalk(t5, (int)(sizeof(t5)/sizeof(t5[0]))) ? "true" : "false");

    return 0;
}