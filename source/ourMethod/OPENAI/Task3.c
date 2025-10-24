#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_LEN 5000000u
#define ALPHABET_MASK ((uint32_t)((1u << 26) - 1u))

bool is_pangram(const char* s) {
    if (s == NULL) {
        return false;
    }
    uint32_t mask = 0u;
    unsigned int count = 0u;

    for (const unsigned char* p = (const unsigned char*)s; *p != '\0'; ++p) {
        count++;
        if (count > MAX_LEN) {
            return false;
        }
        unsigned char ch = *p;
        if (ch >= 'A' && ch <= 'Z') {
            ch = (unsigned char)(ch - 'A' + 'a');
        }
        if (ch >= 'a' && ch <= 'z') {
            mask |= (uint32_t)(1u << (ch - 'a'));
            if (mask == ALPHABET_MASK) {
                return true;
            }
        }
    }
    return mask == ALPHABET_MASK;
}

static void run_test(const char* s) {
    bool result = is_pangram(s);
    printf("%s\n", result ? "true" : "false");
}

int main(void) {
    run_test("The quick brown fox jumps over the lazy dog");
    run_test("Sphinx of black quartz, judge my vow");
    run_test("Hello, World!");
    run_test("Pack my box with five dozen liquor jugs.");
    run_test("");
    return 0;
}