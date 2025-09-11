
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** addLineNumbers(const char** lines, int size) {
    if (lines == NULL || size < 0) {
        return NULL;
    }
    
    char** result = (char**)malloc(size * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        // Allocate memory for line number + ": " + original string + null terminator
        result[i] = (char*)malloc(strlen(lines[i]) + 10);
        if (result[i] == NULL) {
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        sprintf(result[i], "%d: %s", i + 1, lines[i]);
    }
    
    return result;
}

int main() {
    // Test case 1: Empty array
    const char* test1[] = {};
    printf("Test 1: []\\n");
    
    // Test case 2: Array with three elements
    const char* test2[] = {"a", "b", "c"};
    printf("Test 2: ");
    char** result2 = addLineNumbers(test2, 3);
    if (result2) {
        for (int i = 0; i < 3; i++) {
            printf("%s ", result2[i]);
            free(result2[i]);
        }
        free(result2);
    }
    printf("\\n");
    
    // Test case 3: Array with one element
    const char* test3[] = {"hello"};
    printf("Test 3: ");
    char** result3 = addLineNumbers(test3, 1);
    if (result3) {
        printf("%s ", result3[0]);
        free(result3[0]);
        free(result3);
    }
    printf("\\n");
    
    // Test case 4: Array with special characters
    const char* test4[] = {"*", "#", "@"};
    printf("Test 4: ");
    char** result4 = addLineNumbers(test4, 3);
    if (result4) {
        for (int i = 0; i < 3; i++) {
            printf("%s ", result4[i]);
            free(result4[i]);
        }
        free(result4);
    }
    printf("\\n");
    
    // Test case 5: Array with longer strings
    const char* test5[] = {"Line one", "Line two", "Line three"};
    printf("Test 5: ");
    char** result5 = addLineNumbers(test5, 3);
    if (result5) {
        for (int i = 0; i < 3; i++) {
            printf("%s ", result5[i]);
            free(result5[i]);
        }
        free(result5);
    }
    printf("\\n");
    
    return 0;
}
