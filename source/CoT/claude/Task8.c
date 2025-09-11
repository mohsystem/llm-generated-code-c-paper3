
#include <stdio.h>

char findMissingLetter(char array[], int size) {
    // Convert first character to ASCII value
    int start = (int) array[0];
    
    // Loop through array checking for gap in sequence
    for (int i = 0; i < size; i++) {
        if ((int) array[i] != start + i) {
            return (char) (start + i);
        }
    }
    return ' ';
}

int main() {
    // Test cases
    char test1[] = {'a','b','c','d','f'};
    char test2[] = {'O','Q','R','S'};
    char test3[] = {'a','c','d'};
    char test4[] = {'m','o','p','q'};
    char test5[] = {'F','H','I'};
    
    printf("%c\\n", findMissingLetter(test1, 5));  // e
    printf("%c\\n", findMissingLetter(test2, 4));  // P
    printf("%c\\n", findMissingLetter(test3, 3));  // b
    printf("%c\\n", findMissingLetter(test4, 4));  // n
    printf("%c\\n", findMissingLetter(test5, 3));  // G
    
    return 0;
}
