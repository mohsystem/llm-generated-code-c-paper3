#include <stdio.h>

char findMissingLetter(char array[], int len) {
    char expected = array[0];
    for (int i = 0; i < len; i++) {
        char actual = array[i];

        if (actual != expected) {
            return expected;
        }
        expected++;
    }
    return ' '; // Should never reach here based on problem constraints
}

int main() {
    printf("%c\n", findMissingLetter((char[]){'a', 'b', 'c', 'd', 'f'}, 5)); // e
    printf("%c\n", findMissingLetter((char[]){'O', 'Q', 'R', 'S'}, 4)); // P
    printf("%c\n", findMissingLetter((char[]){'w', 'x', 'y', 'z'}, 4)); // Should never reach here based on problem constraints
    printf("%c\n", findMissingLetter((char[]){'A', 'B', 'D'}, 3)); // C
    printf("%c\n", findMissingLetter((char[]){'p', 'q', 's'}, 3)); // r
    return 0;
}