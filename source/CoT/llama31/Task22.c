#include <stdio.h>
#include <stdlib.h>

typedef struct ListItem {
    int isInt;
    union {
        int value;
        char* str;
    } data;
} ListItem;

ListItem* filterList(ListItem* inputList, int length, int* newLength) {
    ListItem* result = (ListItem*)malloc(length * sizeof(ListItem));
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (inputList[i].isInt) {
            result[j].isInt = 1;
            result[j].data.value = inputList[i].data.value;
            j++;
        }
    }
    *newLength = j;
    return result;
}

void printList(ListItem* list, int length) {
    for (int i = 0; i < length; i++) {
        if (list[i].isInt) {
            printf("%d ", list[i].data.value);
        }
    }
    printf("\n");
}

int main() {
    // Test cases
    ListItem test1[] = {{1, {1}}, {1, {2}}, {0, {"a"}}, {0, {"b"}}};
    ListItem test2[] = {{1, {1}}, {0, {"a"}}, {0, {"b"}}, {1, {0}}, {1, {15}}};
    ListItem test3[] = {{1, {1}}, {1, {2}}, {0, {"a"}}, {0, {"b"}}, {0, {"aasf"}}, {0, {"1"}}, {0, {"123"}}, {1, {123}}};
    ListItem test4[] = {{0, {"a"}}, {0, {"b"}}, {0, {"c"}}};
    ListItem test5[] = {{1, {10}}, {1, {20}}, {1, {30}}};

    int newLength;
    ListItem* result1 = filterList(test1, 4, &newLength);
    printList(result1, newLength); // 1 2
    free(result1);

    ListItem* result2 = filterList(test2, 5, &newLength);
    printList(result2, newLength); // 1 0 15
    free(result2);

    ListItem* result3 = filterList(test3, 8, &newLength);
    printList(result3, newLength); // 1 2 123
    free(result3);

    ListItem* result4 = filterList(test4, 3, &newLength);
    printList(result4, newLength); // 
    free(result4);

    ListItem* result5 = filterList(test5, 3, &newLength);
    printList(result5, newLength); // 10 20 30
    free(result5);

    return 0;
}