#include <stdio.h>

char findMissingLetter(char array[], int size) {
    char expected = array[0];
    for (int i = 1; i < size; i++) {
        expected++;
        if (array[i] != expected) {
            return expected;
        }
    }
    return ' '; // Should never reach here
}

int main() {
    char test1[] = {'a', 'b', 'c', 'd', 'f'};
    char test2[] = {'O', 'Q', 'R', 'S'};
    char test3[] = {'w', 'x', 'y', 'z'};
    char test4[] = {'A', 'B', 'D'};
    char test5[] = {'p', 'q', 'r', 's', 't', 'v'};

    printf("Test 1: %c\n", findMissingLetter(test1, sizeof(test1))); // e
    printf("Test 2: %c\n", findMissingLetter(test2, sizeof(test2))); // P
    printf("Test 3: %c\n", findMissingLetter(test3, sizeof(test3))); // (none)
    printf("Test 4: %c\n", findMissingLetter(test4, sizeof(test4))); // C
    printf("Test 5: %c\n", findMissingLetter(test5, sizeof(test5))); // u

    return 0;
}