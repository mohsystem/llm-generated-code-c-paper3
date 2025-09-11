
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** number_lines(const char** lines, int size) {
    if (size == 0 || lines == NULL) {
        return NULL;
    }
    
    char** result = (char**)malloc(size * sizeof(char*));
    if (!result) return NULL;
    
    for (int i = 0; i < size; i++) {
        // Calculate required size for new string
        int num_len = snprintf(NULL, 0, "%d", i + 1);
        int total_len = num_len + 2 + strlen(lines[i]) + 1; // +2 for ": ", +1 for null terminator
        
        result[i] = (char*)malloc(total_len);
        if (!result[i]) {
            // Clean up previously allocated memory if malloc fails
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        snprintf(result[i], total_len, "%d: %s", i + 1, lines[i]);
    }
    
    return result;
}

void free_string_array(char** arr, int size) {
    if (arr) {
        for (int i = 0; i < size; i++) {
            free(arr[i]);
        }
        free(arr);
    }
}

int main() {
    // Test case 1: Empty array
    const char* test1[] = {};
    char** result1 = number_lines(test1, 0);
    printf("Test 1: (empty array)\\n");
    free_string_array(result1, 0);
    
    // Test case 2: Single line
    const char* test2[] = {"a"};
    char** result2 = number_lines(test2, 1);
    printf("Test 2: %s\\n", result2[0]);
    free_string_array(result2, 1);
    
    // Test case 3: Multiple lines
    const char* test3[] = {"a", "b", "c"};
    char** result3 = number_lines(test3, 3);
    printf("Test 3: %s, %s, %s\\n", result3[0], result3[1], result3[2]);
    free_string_array(result3, 3);
    
    // Test case 4: Lines with spaces
    const char* test4[] = {"Line 1", "Line 2", "Line 3"};
    char** result4 = number_lines(test4, 3);
    printf("Test 4: %s, %s, %s\\n", result4[0], result4[1], result4[2]);
    free_string_array(result4, 3);
    
    // Test case 5: Lines with special characters
    const char* test5[] = {"Hello!", "@World", "#Test"};
    char** result5 = number_lines(test5, 3);
    printf("Test 5: %s, %s, %s\\n", result5[0], result5[1], result5[2]);
    free_string_array(result5, 3);
    
    return 0;
}
