#include <stdio.h>

char findMissingLetter(const char* array, size_t length) {
    for (size_t i = 1; i < length; i++) {
        if (array[i] - array[i - 1] != 1) {
            return array[i - 1] + 1;
        }
    }
    return ' ';
}

int main() {
    char array1[] = {'a', 'b', 'c', 'd', 'f'};
    char array2[] = {'O', 'Q', 'R', 'S'};
    printf("%c\n", findMissingLetter(array1, sizeof(array1) / sizeof(array1[0])));  // 'e'
    printf("%c\n", findMissingLetter(array2, sizeof(array2) / sizeof(array2[0])));  // 'P'
    return 0;
}