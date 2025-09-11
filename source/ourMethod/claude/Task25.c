
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** add_line_numbers(const char** lines, size_t count, size_t* result_count) {
    if (lines == NULL || result_count == NULL) {
        if (result_count) *result_count = 0;
        return NULL;
    }
    
    *result_count = count;
    if (count == 0) return NULL;
    
    char** result = (char**)malloc(count * sizeof(char*));
    if (!result) {
        *result_count = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        // Calculate required buffer size
        size_t len = snprintf(NULL, 0, "%zu: %s", i + 1, lines[i] ? lines[i] : "") + 1;
        result[i] = (char*)malloc(len);
        
        if (!result[i]) {
            // Clean up on allocation failure
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }
        
        snprintf(result[i], len, "%zu: %s", i + 1, lines[i] ? lines[i] : "");
    }
    
    return result;
}

int main() {
    // Test cases
    const char* tests[][5] = {
        {},
        {"a", "b", "c"},
        {"1", "2", "3", "4", "5"},
        {NULL, "test", NULL},
        {"Hello", "World!"}
    };
    
    size_t test_sizes[] = {0, 3, 5, 3, 2};
    
    for (size_t i = 0; i < sizeof(test_sizes)/sizeof(test_sizes[0]); i++) {
        printf("Test case %zu:\\n", i + 1);
        
        size_t result_count;
        char** result = add_line_numbers(tests[i], test_sizes[i], &result_count);
        
        printf("Input: [");
        for (size_t j = 0; j < test_sizes[i]; j++) {
            printf("%s%s", j > 0 ? ", " : "", tests[i][j] ? tests[i][j] : "NULL");
        }
        printf("]\\n");
        
        printf("Output: [");
        for (size_t j = 0; j < result_count; j++) {
            printf("%s%s", j > 0 ? ", " : "", result[j]);
        }
        printf("]\\n\\n");
        
        // Clean up
        if (result) {
            for (size_t j = 0; j < result_count; j++) {
                free(result[j]);
            }
            free(result);
        }
    }
    
    return 0;
}
