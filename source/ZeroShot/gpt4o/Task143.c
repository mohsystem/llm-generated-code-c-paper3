#include <stdio.h>
#include <stdlib.h>

void sortArray(int* array, int size) {
    qsort(array, size, sizeof(int), (int (*)(const void*, const void*))compare);
}

int compare(const int* a, const int* b) {
    return (*a - *b);
}

int main() {
    int test1[] = {5, 2, 9, 1, 5, 6};
    int test2[] = {3, 0, -2, 5, 1};
    int test3[] = {10, 20, 30, 40, 50};
    int test4[] = {4, 3, 2, 1};
    int test5[] = {0};

    int sizes[] = {6, 5, 5, 4, 1};

    int* tests[] = {test1, test2, test3, test4, test5};

    for (int i = 0; i < 5; i++) {
        sortArray(tests[i], sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", tests[i][j]);
        }
        printf("\n");
    }

    return 0;
}