#include <stdio.h>
#include <stdlib.h>

void sortArray(int array[], int n) {
    qsort(array, n, sizeof(int), compare);
}

int compare(const void * a, const void * b) {
    return ( * (int *) a - * (int *) b );
}

int main() {
    int array[] = {5, 3, 8, 2, 1};
    int n = sizeof(array) / sizeof(array[0]);
    sortArray(array, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}