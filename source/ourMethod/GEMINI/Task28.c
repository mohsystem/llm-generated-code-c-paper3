#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a display text for "likes" based on an array of names.
 *
 * @param names An array of C-strings.
 * @param count The number of names in the array.
 * @return A dynamically allocated string which must be freed by the caller.
 *         Returns NULL on memory allocation failure.
 */
char* whoLikesIt(const char* const names[], int count) {
    char* result = NULL;
    int size = 0;

    // Rule #1: Validate input. A negative count is invalid.
    if (count < 0) {
        count = 0;
    }

    switch (count) {
        case 0: {
            const char* msg = "no one likes this";
            size = strlen(msg) + 1;
            result = (char*)malloc(size);
            if (result == NULL) return NULL; // Rule #7: Check malloc return
            // Rule #2, #3, #7: Use snprintf for safe string formatting
            snprintf(result, size, "%s", msg);
            break;
        }
        case 1: {
            const char* fmt = "%s likes this";
            size = snprintf(NULL, 0, fmt, names[0]) + 1;
            result = (char*)malloc(size);
            if (result == NULL) return NULL;
            snprintf(result, size, fmt, names[0]);
            break;
        }
        case 2: {
            const char* fmt = "%s and %s like this";
            size = snprintf(NULL, 0, fmt, names[0], names[1]) + 1;
            result = (char*)malloc(size);
            if (result == NULL) return NULL;
            snprintf(result, size, fmt, names[0], names[1]);
            break;
        }
        case 3: {
            const char* fmt = "%s, %s and %s like this";
            size = snprintf(NULL, 0, fmt, names[0], names[1], names[2]) + 1;
            result = (char*)malloc(size);
            if (result == NULL) return NULL;
            snprintf(result, size, fmt, names[0], names[1], names[2]);
            break;
        }
        default: {
            const char* fmt = "%s, %s and %d others like this";
            size = snprintf(NULL, 0, fmt, names[0], names[1], count - 2) + 1;
            result = (char*)malloc(size);
            if (result == NULL) return NULL;
            snprintf(result, size, fmt, names[0], names[1], count - 2);
            break;
        }
    }
    return result;
}

void print_array(const char* const arr[], int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("\"%s\"", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void run_test(const char* const names[], int count) {
    print_array(names, count);
    char* output = whoLikesIt(names, count);
    if (output) {
        printf(" -> Output: \"%s\"\n", output);
        free(output); // Rule #7: Free allocated memory
    } else {
        printf(" -> Memory allocation failed!\n");
    }
}

int main() {
    // Test case 1
    const char* test1[] = {};
    run_test(test1, 0);

    // Test case 2
    const char* test2[] = {"Peter"};
    run_test(test2, 1);

    // Test case 3
    const char* test3[] = {"Jacob", "Alex"};
    run_test(test3, 2);

    // Test case 4
    const char* test4[] = {"Max", "John", "Mark"};
    run_test(test4, 3);

    // Test case 5
    const char* test5[] = {"Alex", "Jacob", "Mark", "Max"};
    run_test(test5, 4);

    return 0;
}