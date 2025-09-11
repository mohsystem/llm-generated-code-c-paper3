
#include <stdio.h>
#include <stdlib.h>

char findMissingLetter(const char* array, int size) {
    // Check valid input
    if (array == NULL || size < 2) {
        fprintf(stderr, "Invalid input array\\n");
        return ' ';
    }

    // Check consecutive letters
    for (int i = 0; i < size-1; i++) {
        char current = array[i];
        char next = array[i+1];
        
        // If gap more than 1, missing letter found
        if (next - current > 1) {
            return current + 1;
        }
    }
    
    return ' '; // Should not reach here with valid input
}

int main() {
    // Test cases
    char test1[] = {'a','b','c','d','f'};
    char test2[] = {'O','Q','R','S'};
    char test3[] = {'a','c','d'};
    char test4[] = {'X','Z'};
    char test5[] = {'m','n','p','q'};

    printf("%c\\n", findMissingLetter(test1, 5)); // e
    printf("%c\\n", findMissingLetter(test2, 4)); // P
    printf("%c\\n", findMissingLetter(test3, 3)); // b
    printf("%c\\n", findMissingLetter(test4, 2)); // Y
    printf("%c\\n", findMissingLetter(test5, 4)); // o

    return 0;
}
