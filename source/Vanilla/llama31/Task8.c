#include <stdio.h>

char findMissingLetter(char letters[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (letters[i + 1] - letters[i] > 1) {
            return letters[i] + 1;
        }
    }
    return ' '; // This line should not be reached if input is valid
}

int main() {
    char test1[] = {'a', 'b', 'c', 'd', 'f', '\0'};
    char test2[] = {'O', 'Q', 'R', 'S', '\0'};
    char test3[] = {'a', 'b', 'c', 'e', '\0'};
    char test4[] = {'x', 'y', 'z', 'a', '\0'};
    char test5[] = {'A', 'B', 'C', 'E', '\0'};

    printf("%c\n", findMissingLetter(test1, 5)); // e
    printf("%c\n", findMissingLetter(test2, 4)); // P
    printf("%c\n", findMissingLetter(test3, 4)); // d
    printf("%c\n", findMissingLetter(test4, 4)); // This case is invalid as 'a' is not consecutive with 'z'
    printf("%c\n", findMissingLetter(test5, 4)); // D

    return 0;
}