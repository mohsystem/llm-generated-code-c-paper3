#include <stdio.h>

char findMissingLetter(const char* chars, size_t length) {
    for (size_t i = 1; i < length; i++) {
        if (chars[i] - chars[i - 1] > 1) {
            return chars[i - 1] + 1;
        }
    }
    return '\0';
}

int main() {
    const char chars1[] = {'a', 'b', 'c', 'd', 'f'};
    printf("%c\n", findMissingLetter(chars1, sizeof(chars1) / sizeof(chars1[0])));  // 'e'

    const char chars2[] = {'O', 'Q', 'R', 'S'};
    printf("%c\n", findMissingLetter(chars2, sizeof(chars2) / sizeof(chars2[0])));  // 'P'

    return 0;
}