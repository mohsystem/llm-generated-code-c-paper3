#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a structure to hold integer and string values.
typedef struct {
    enum { INT_TYPE, STRING_TYPE } type;
    union {
        int intValue;
        char *stringValue;
    } value;
} IntOrString;


// Function to filter out strings from a list of IntOrString.

IntOrString *filter_list(IntOrString *list, int size, int *new_size) {

    IntOrString *filtered_list = malloc(sizeof(IntOrString) * size); // Allocate maximum possible size initially
    *new_size = 0;


    for (int i = 0; i < size; i++) {
        if (list[i].type == INT_TYPE) {
            filtered_list[(*new_size)++] = list[i]; 
        }

    }


    // Reallocate to the actual size
    filtered_list = realloc(filtered_list, sizeof(IntOrString) * (*new_size));


    return filtered_list;
}

int main() {
    IntOrString test1[] = {
        {.type = INT_TYPE, .value.intValue = 1},
        {.type = INT_TYPE, .value.intValue = 2},
        {.type = STRING_TYPE, .value.stringValue = "a"},
        {.type = STRING_TYPE, .value.stringValue = "b"}
    };
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int new_size1;
    IntOrString *result1 = filter_list(test1, size1, &new_size1);


    for (int i = 0; i < new_size1; i++) {
        printf("%d ", result1[i].value.intValue);
    }
    printf("\n");
    free(result1);


    // Test cases 2-5 (similar structure to test case 1)

    return 0;
}