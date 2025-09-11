#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a structure to hold any data type
typedef struct {
    enum { INT, STRING } type;
    union {
        int ival;
        char *sval;
    } value;
} Any;

// Function to filter the list
Any *filter_list(Any *list, int size, int *new_size) {
    Any *result = malloc(size * sizeof(Any)); // Allocate maximum possible size initially
    *new_size = 0;

    for (int i = 0; i < size; i++) {
        if (list[i].type == INT) {
            result[(*new_size)++] = list[i];
        }
    }
    // Reallocate memory to the actual size of the filtered list
    return realloc(result, *new_size * sizeof(Any));
}


int main() {
     Any list1[] = {{.type = INT, .value.ival = 1}, {.type = INT, .value.ival = 2}, {.type = STRING, .value.sval = "a"}, {.type = STRING, .value.sval = "b"}};
    int new_size1;
    Any *result1 = filter_list(list1, 4, &new_size1);
     printf("[");
    for (int i = 0; i < new_size1; i++) {
        printf("%d%s", result1[i].value.ival, i < new_size1 - 1 ? ", " : "");
    }
    printf("]\n");
    free(result1);

    return 0;
}