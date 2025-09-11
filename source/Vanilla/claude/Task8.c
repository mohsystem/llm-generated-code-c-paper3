
#include <stdio.h>

char findMissingLetter(char array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i + 1] - array[i] > 1) {
            return array[i] + 1;
        }
    }
    return ' ';
}

int main() {
    // Test cases
    char arr1[] = {'a','b','c','d','f'};
    char arr2[] = {'O','Q','R','S'};
    char arr3[] = {'a','b','d'};
    char arr4[] = {'m','o'};
    char arr5[] = {'G','I','J'};
    
    printf("%c\\n", findMissingLetter(arr1, 5));  // e
    printf("%c\\n", findMissingLetter(arr2, 4));  // P
    printf("%c\\n", findMissingLetter(arr3, 3));  // c
    printf("%c\\n", findMissingLetter(arr4, 2));  // n
    printf("%c\\n", findMissingLetter(arr5, 3));  // H
    
    return 0;
}
