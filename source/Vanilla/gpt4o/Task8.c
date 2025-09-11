#include <stdio.h>

char findMissingLetter(char array[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if (array[i + 1] != array[i] + 1) {
            return array[i] + 1;
        }
    }
    return ' '; // This should never be reached with valid input
}

int main() {
    printf("%c\n", findMissingLetter((char[]){'a', 'b', 'c', 'd', 'f'}, 5)); // e
    printf("%c\n", findMissingLetter((char[]){'O', 'Q', 'R', 'S'}, 4));      // P
    printf("%c\n", findMissingLetter((char[]){'m', 'n', 'p', 'q'}, 4));      // o
    printf("%c\n", findMissingLetter((char[]){'E', 'F', 'H'}, 3));           // G
    printf("%c\n", findMissingLetter((char[]){'x', 'y', 'z'}, 3));           // (shouldn't reach here with valid input)
    return 0;
}