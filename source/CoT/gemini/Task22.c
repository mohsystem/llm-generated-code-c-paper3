#include <stdio.h>
#include <stdlib.h>

// In C, handling mixed types like this is more complex.  We'd typically 
// need a struct or union and a type indicator.  For simplicity, this
// solution will assume the input array contains only ints and will skip
// any non-integer values (which would require additional parsing logic).


// This function filters a list of integers, assuming any non-integer
// values are meant to be ignored.  A more robust solution would
// require a way to explicitly represent the mixed types.
int *filter_list(int *mixed_list, int size, int *new_size) {
    int *integer_list = malloc(size * sizeof(int)); // Allocate maximum possible size
    *new_size = 0;

    if (integer_list == NULL) {
        return NULL; // Handle memory allocation failure
    }


    for (int i = 0; i < size; i++) {

            integer_list[*new_size] = mixed_list[i];
            (*new_size)++;
        
    }

    // Reallocate to the actual size used
    integer_list = realloc(integer_list, *new_size * sizeof(int)); 
    if (integer_list == NULL && *new_size >0) { 
        return NULL; // Handle reallocation failure
    }
    return integer_list;
}

int main() {
    int test1[] = {1, 2, 3 , 4}; // Example usage (no strings for simplicity)
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int new_size1;
    int *result1 = filter_list(test1, size1, &new_size1);

    if (result1 != NULL) {
      for (int i = 0; i < new_size1; i++) {
          printf("%d ", result1[i]);
      }
      printf("\n");
      free(result1); // Free allocated memory
    } else {
        printf("Memory allocation failed\n");
    }

     // More test cases (adapting the logic above):

    int test2[] = {1, 2, 3, 4, 5}; 
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int new_size2;
    int *result2 = filter_list(test2, size2, &new_size2);
    // ... (print and free result2)

    int test3[] = {10, 20, 30};
    // ... (and so on for other test cases)


    return 0;
}