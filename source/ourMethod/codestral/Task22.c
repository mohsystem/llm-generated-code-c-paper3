#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    STRING
} Type;

typedef struct {
    Type type;
    union {
        int intValue;
        char* stringValue;
    };
} Value;

int* filterList(const Value* list, int length, int* resultLength) {
    int* result = malloc(length * sizeof(int));
    *resultLength = 0;
    for (int i = 0; i < length; i++) {
        if (list[i].type == INT) {
            result[(*resultLength)++] = list[i].intValue;
        }
    }
    return result;
}

int main() {
    Value list1[] = {{INT, 1}, {INT, 2}, {STRING, "a"}, {STRING, "b"}};
    int resultLength1;
    int* result1 = filterList(list1, 4, &resultLength1);
    for (int i = 0; i < resultLength1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n"); // prints: 1 2
    free(result1);

    Value list2[] = {{INT, 1}, {STRING, "a"}, {STRING, "b"}, {INT, 0}, {INT, 15}};
    int resultLength2;
    int* result2 = filterList(list2, 5, &resultLength2);
    for (int i = 0; i < resultLength2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n"); // prints: 1 0 15
    free(result2);

    Value list3[] = {{INT, 1}, {INT, 2}, {STRING, "a"}, {STRING, "b"}, {STRING, "aasf"}, {STRING, "1"}, {STRING, "123"}, {INT, 123}};
    int resultLength3;
    int* result3 = filterList(list3, 8, &resultLength3);
    for (int i = 0; i < resultLength3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n"); // prints: 1 2 123
    free(result3);

    return 0;
}