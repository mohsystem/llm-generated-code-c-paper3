
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a variant type (either int or string)
typedef struct {
    int type;  // 0 for int, 1 for string
    union {
        int i;
        char* s;
    } value;
} Variant;

int* filterList(Variant* list, int size, int* resultSize) {
    if (!list || size < 0 || !resultSize) {
        *resultSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(size * sizeof(int));
    if (!result) {
        *resultSize = 0;
        return NULL;
    }
    
    *resultSize = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].type == 0 && list[i].value.i >= 0) {
            result[*resultSize] = list[i].value.i;
            (*resultSize)++;
        }
    }
    
    return result;
}

int main() {
    // Test case 1
    Variant test1[] = {{0, {.i=1}}, {0, {.i=2}}, {1, {.s="a"}}, {1, {.s="b"}}};
    int size1;
    int* result1 = filterList(test1, 4, &size1);
    for (int i = 0; i < size1; i++) printf("%d ", result1[i]);
    printf("\\n");
    free(result1);
    
    // Test case 2
    Variant test2[] = {{0, {.i=1}}, {1, {.s="a"}}, {1, {.s="b"}}, {0, {.i=0}}, {0, {.i=15}}};
    int size2;
    int* result2 = filterList(test2, 5, &size2);
    for (int i = 0; i < size2; i++) printf("%d ", result2[i]);
    printf("\\n");
    free(result2);
    
    // Test case 3
    Variant test3[] = {{0, {.i=1}}, {0, {.i=2}}, {1, {.s="a"}}, {1, {.s="b"}}, 
                       {1, {.s="aasf"}}, {1, {.s="1"}}, {1, {.s="123"}}, {0, {.i=123}}};
    int size3;
    int* result3 = filterList(test3, 8, &size3);
    for (int i = 0; i < size3; i++) printf("%d ", result3[i]);
    printf("\\n");
    free(result3);
    
    // Test case 4
    int size4;
    int* result4 = filterList(NULL, 0, &size4);
    printf("Empty list\\n");
    free(result4);
    
    // Test case 5
    Variant test5[] = {{1, {.s="string"}}, {1, {.s="only"}}, {1, {.s="list"}}};
    int size5;
    int* result5 = filterList(test5, 3, &size5);
    for (int i = 0; i < size5; i++) printf("%d ", result5[i]);
    printf("\\n");
    free(result5);
    
    return 0;
}
