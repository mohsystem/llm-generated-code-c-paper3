// Note: C does not natively support mixed-type lists or filtering as in the other languages.
// This example uses a simple array and manual iteration to filter integers.
#include <stdio.h>
#include <stdlib.h>

void filterList(int* list, int listSize, int** filteredList, int* filteredSize) {
    int count = 0;
    for (int i = 0; i < listSize; i++) {
        if (list[i] >= 0) { // Assuming non-negative integers
            count++;
        }
    }

    *filteredSize = count;
    *filteredList = (int*)malloc(count * sizeof(int));
    int j = 0;
    for (int i = 0; i < listSize; i++) {
        if (list[i] >= 0) { // Assuming non-negative integers
            (*filteredList)[j++] = list[i];
        }
    }
}

int main() {
    int list1[] = {1, 2, -1, 0, 15};
    int list2[] = {1, -1, -1, 0, 15};
    int list3[] = {1, 2, -1, -1, -1, 123};
    int list4[] = {-1, -1, -1};
    int list5[] = {10, 20, 30};

    int sizes[] = {sizeof(list1)/sizeof(list1[0]), sizeof(list2)/sizeof(list2[0]), sizeof(list3)/sizeof(list3[0]), sizeof(list4)/sizeof(list4[0]), sizeof(list5)/sizeof(list5[0])};

    for (int i = 0; i < 5; i++) {
        int* filteredList;
        int filteredSize;
        filterList((i == 0) ? list1 : (i == 1) ? list2 : (i == 2) ? list3 : (i == 3) ? list4 : list5, sizes[i], &filteredList, &filteredSize);
        for (int j = 0; j < filteredSize; j++) {
            printf("%d ", filteredList[j]);
        }
        printf("\n");
        free(filteredList);
    }

    return 0;
}