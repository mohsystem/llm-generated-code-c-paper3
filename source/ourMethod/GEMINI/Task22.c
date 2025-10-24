#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a tagged union to represent a list of mixed types.
typedef enum {
    TYPE_INT,
    TYPE_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        int int_val;
        const char* str_val;
    } value;
} Element;

/**
 * @brief Filters a list of Elements, returning a new array with only non-negative integers.
 * 
 * @param list The input array of Element structs.
 * @param count The number of elements in the input array.
 * @param out_count A pointer to a size_t variable where the size of the output array will be stored.
 * @return A dynamically allocated array of integers. The caller must free this memory.
 *         Returns NULL on allocation failure or if no integers are found.
 */
int* filter_list(const Element* list, size_t count, size_t* out_count) {
    // Rule #1: Validate inputs.
    if (list == NULL || out_count == NULL) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    *out_count = 0;
    if (count == 0) {
        return NULL;
    }

    // Rule #3: Allocate memory safely.
    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL; // Allocation failure
    }

    size_t result_count = 0;
    for (size_t i = 0; i < count; ++i) {
        // Rule #1: Check the type and value of each element.
        if (list[i].type == TYPE_INT && list[i].value.int_val >= 0) {
            result[result_count++] = list[i].value.int_val;
        }
    }

    if (result_count == 0) {
        free(result);
        return NULL;
    }

    // Optional: Shrink allocation to fit the actual number of elements.
    int* final_result = (int*)realloc(result, result_count * sizeof(int));
    if (final_result == NULL) {
        // realloc failed; return original larger block.
        *out_count = result_count;
        return result;
    }
    
    *out_count = result_count;
    return final_result;
}

void print_element_list(const Element* list, size_t count) {
    printf("[");
    for (size_t i = 0; i < count; ++i) {
        if (list[i].type == TYPE_INT) {
            printf("%d", list[i].value.int_val);
        } else {
            printf("\"%s\"", list[i].value.str_val);
        }
        if (i < count - 1) printf(", ");
    }
    printf("]");
}

void print_int_array(const int* arr, size_t count) {
    printf("[");
    for (size_t i = 0; i < count; ++i) {
        printf("%d", arr[i]);
        if (i < count - 1) printf(", ");
    }
    printf("]");
}

void run_test_case(const char* name, Element* list, size_t count) {
    printf("%s\n", name);
    printf("Input: ");
    print_element_list(list, count);
    
    size_t out_count = 0;
    int* filtered = filter_list(list, count, &out_count);

    printf(", Output: ");
    if (filtered) {
        print_int_array(filtered, out_count);
        free(filtered); // Rule #6: Free allocated memory.
    } else {
        printf("[]");
    }
    printf("\n");
}

int main() {
    // 5 test cases
    
    // Test Case 1
    Element list1[] = {{.type=TYPE_INT, .value.int_val=1}, {.type=TYPE_INT, .value.int_val=2}, {.type=TYPE_STRING, .value.str_val="a"}, {.type=TYPE_STRING, .value.str_val="b"}};
    run_test_case("Test Case 1", list1, sizeof(list1)/sizeof(Element));

    // Test Case 2
    Element list2[] = {{.type=TYPE_INT, .value.int_val=1}, {.type=TYPE_STRING, .value.str_val="a"}, {.type=TYPE_STRING, .value.str_val="b"}, {.type=TYPE_INT, .value.int_val=0}, {.type=TYPE_INT, .value.int_val=15}};
    run_test_case("Test Case 2", list2, sizeof(list2)/sizeof(Element));

    // Test Case 3
    Element list3[] = {{.type=TYPE_INT, .value.int_val=1}, {.type=TYPE_INT, .value.int_val=2}, {.type=TYPE_STRING, .value.str_val="aasf"}, {.type=TYPE_STRING, .value.str_val="1"}, {.type=TYPE_STRING, .value.str_val="123"}, {.type=TYPE_INT, .value.int_val=123}};
    run_test_case("Test Case 3", list3, sizeof(list3)/sizeof(Element));

    // Test Case 4: Contains negative numbers which should be filtered out
    Element list4[] = {{.type=TYPE_STRING, .value.str_val="hello"}, {.type=TYPE_STRING, .value.str_val="world"}, {.type=TYPE_INT, .value.int_val=-1}, {.type=TYPE_INT, .value.int_val=5}, {.type=TYPE_INT, .value.int_val=-10}};
    run_test_case("Test Case 4", list4, sizeof(list4)/sizeof(Element));
    
    // Test Case 5: Empty list
    run_test_case("Test Case 5", NULL, 0);

    return 0;
}