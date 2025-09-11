#include <stdio.h>
#include <stdlib.h>

char findMissingLetter(const char array[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if (array[i + 1] != array[i] + 1) {
            return array[i] + 1;
        }
    }
    fprintf(stderr, "No missing letter found.\n");
    exit(EXIT_FAILURE);
}

int main() {
    printf("%c\n", findMissingLetter((char[]){'a', 'b', 'c', 'd', 'f'}, 5)); // e
    printf("%c\n", findMissingLetter((char[]){'O', 'Q', 'R', 'S'}, 4)); // P
    printf("%c\n", findMissingLetter((char[]){'x', 'y', 'z', 'a'}, 4)); // exit
    printf("%c\n", findMissingLetter((char[]){'J', 'K', 'M'}, 3)); // L
    printf("%c\n", findMissingLetter((char[]){'u', 'v', 'w', 'y'}, 4)); // x
    return 0;
}