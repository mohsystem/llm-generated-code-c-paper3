#include <stdio.h>

char findMissingLetter(char array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i + 1] != array[i] + 1) {
            return array[i] + 1;
        }
    }
    return ' '; // Default return, should not reach here as per problem constraints
}

int main() {
    printf("%c\n", findMissingLetter((char[]){'a', 'b', 'c', 'd', 'f'}, 5)); // e
    printf("%c\n", findMissingLetter((char[]){'O', 'Q', 'R', 'S'}, 4)); // P
    printf("%c\n", findMissingLetter((char[]){'x', 'y', 'z', 'b'}, 4)); // a
    printf("%c\n", findMissingLetter((char[]){'K', 'M', 'N', 'O'}, 4)); // L
    printf("%c\n", findMissingLetter((char[]){'B', 'C', 'D', 'F'}, 4)); // E
    return 0;
}