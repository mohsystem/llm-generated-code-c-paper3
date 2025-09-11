#include <stdio.h>
#include <string.h>

char findMissingLetter(char array[], int size) {
    for (int i = 1; i < size; i++) {
        if (array[i] - array[i - 1] != 1) {
            return (char)(array[i - 1] + 1);
        }
    }
    return ' '; // Should never reach here
}

int main() {
    char arr1[] = {'a', 'b', 'c', 'd', 'f'};
    printf("%c\n", findMissingLetter(arr1, strlen(arr1))); // e
    char arr2[] = {'O', 'Q', 'R', 'S'};
    printf("%c\n", findMissingLetter(arr2, strlen(arr2))); // P
    char arr3[] = {'A', 'B', 'D'};
    printf("%c\n", findMissingLetter(arr3, strlen(arr3))); // C
    char arr4[] = {'w', 'x', 'y', 'z', 'A'};
    printf("%c\n", findMissingLetter(arr4, strlen(arr4))); // Invalid Input according to problem statement but still handles it safely.
    char arr5[] = {'p', 'q', 'r', 's'};
    printf("%c\n", findMissingLetter(arr5, strlen(arr5))); // Should print nothing.


    return 0;
}