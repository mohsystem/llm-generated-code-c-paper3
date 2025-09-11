#include <stdio.h>

char findMissingLetter(char *array, int size) {
    for (int i = 1; i < size; i++) {
        if (array[i] - array[i - 1] > 1) {
            return (char) (array[i - 1] + 1);
        }
    }
    return '\0';
}

int main() {
    char arr1[] = {'a', 'b', 'c', 'd', 'f'};
    char arr2[] = {'O', 'Q', 'R', 'S'};
    printf("%c\n", findMissingLetter(arr1, 5)); // e
    printf("%c\n", findMissingLetter(arr2, 4)); // P
    return 0;
}