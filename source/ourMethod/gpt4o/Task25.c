#include <stdio.h>
#include <string.h>

void numberLines(const char* lines[], int size, char* result[]) {
    for (int i = 0; i < size; ++i) {
        char buffer[100];
        sprintf(buffer, "%d: %s", i + 1, lines[i]);
        result[i] = strdup(buffer);
    }
}

int main() {
    const char* test1[] = {};
    const char* test2[] = {"a", "b", "c"};
    const char* test3[] = {"Hello", "World"};
    const char* test4[] = {"Line 1", "Line 2", "Line 3", "Line 4"};
    const char* test5[] = {"Single Line"};
    
    char* result[5][4]; // To hold results for each test case
    
    numberLines(test1, 0, result[0]);
    numberLines(test2, 3, result[1]);
    numberLines(test3, 2, result[2]);
    numberLines(test4, 4, result[3]);
    numberLines(test5, 1, result[4]);
    
    // Printing results
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < (i == 0 ? 0 : i + 1); ++j) {
            printf("%s\n", result[i][j]);
            free(result[i][j]); // Freeing allocated memory
        }
    }

    return 0;
}