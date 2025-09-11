#include <stdio.h>

char findMissingLetter(char array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i + 1] - array[i] != 1) {
            return (char)(array[i] + 1);
        }
    }
    return '\0'; // should never reach here as there's always a missing letter
}

int main() {
    printf("%c\n", findMissingLetter((char[]){'a', 'b', 'c', 'd', 'f'}, 5)); // e
    printf("%c\n", findMissingLetter((char[]){'O', 'Q', 'R', 'S'}, 4)); // P
    printf("%c\n", findMissingLetter((char[]){'m', 'n', 'p'}, 3)); // o
    printf("%c\n", findMissingLetter((char[]){'G', 'H', 'J'}, 3)); // I
    printf("%c\n", findMissingLetter((char[]){'x', 'y', 'z', 'b'}, 4)); // a
    return 0;
}