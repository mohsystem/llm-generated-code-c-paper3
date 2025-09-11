
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int type;  // 0 for int, 1 for string
    union {
        int i;
        char* s;
    } value;
} ListItem;

int* filterList(ListItem* list, int size, int* resultSize) {
    if (!list || size < 0 || !resultSize) {
        *resultSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(sizeof(int) * size);
    if (!result) {
        *resultSize = 0;
        return NULL;
    }
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].type == 0 && list[i].value.i >= 0) {
            result[count++] = list[i].value.i;
        }
    }
    
    if (count == 0) {
        free(result);
        *resultSize = 0;
        return NULL;
    }
    
    int* finalResult = (int*)realloc(result, sizeof(int) * count);
    if (!finalResult) {
        free(result);
        *resultSize = 0;
        return NULL;
    }
    
    *resultSize = count;
    return finalResult;
}

int main() {
    // Test case 1
    ListItem test1[] = {
        {0, {.i = 1}},
        {0, {.i = 2}},
        {1, {.s = "a"}},
        {1, {.s = "b"}}
    };
    int resultSize;
    int* result = filterList(test1, 4, &resultSize);
    for(int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]); // 1 2
    }
    printf("\\n");
    free(result);
    
    // Test case 2
    ListItem test2[] = {
        {0, {.i = 1}},
        {1, {.s = "a"}},
        {1, {.s = "b"}},
        {0, {.i = 0}},
        {0, {.i = 15}}
    };
    result = filterList(test2, 5, &resultSize);
    for(int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]); // 1 0 15
    }
    printf("\\n");
    free(result);
    
    return 0;
}
