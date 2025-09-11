
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** number(const char** lines, size_t size) {
    if(size == 0) return NULL;
    
    char** result = (char**)malloc(size * sizeof(char*));
    for(size_t i = 0; i < size; i++) {
        result[i] = (char*)malloc(strlen(lines[i]) + 20); // Extra space for number and ": "
        sprintf(result[i], "%zu: %s", i+1, lines[i]);
    }
    return result;
}

int main() {
    // Test cases
    const char* test1[] = {};
    const char* test2[] = {"a", "b", "c"};
    const char* test3[] = {"", "", ""};
    const char* test4[] = {"Hello", "World"};
    const char* test5[] = {"1", "2", "3", "4", "5"};

    // Test case arrays
    const char** tests[] = {test1, test2, test3, test4, test5};
    size_t sizes[] = {0, 3, 3, 2, 5};

    for(int i = 0; i < 5; i++) {
        printf("Input: [");
        for(size_t j = 0; j < sizes[i]; j++) {
            if(j > 0) printf(", ");
            printf("%s", tests[i][j]);
        }
        printf("]\\n");

        char** result = number(tests[i], sizes[i]);
        if(result) {
            printf("Output: [");
            for(size_t j = 0; j < sizes[i]; j++) {
                if(j > 0) printf(", ");
                printf("%s", result[j]);
                free(result[j]);
            }
            printf("]\\n");
            free(result);
        } else {
            printf("Output: []\\n");
        }
        printf("\\n");
    }
    return 0;
}
