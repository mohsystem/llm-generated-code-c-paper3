#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* low;
    int* high;
    int lowSize;
    int highSize;
    int lowCapacity;
    int highCapacity;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->low = (int*)malloc(50000 * sizeof(int));
    obj->high = (int*)malloc(50000 * sizeof(int));
    obj->lowSize = 0;
    obj->highSize = 0;
    obj->lowCapacity = 50000;
    obj->highCapacity = 50000;
    return obj;
}

void addNum(MedianFinder* obj, int num) {
    obj->low[obj->lowSize++] = num;
    for (int i = obj->lowSize - 1; i > 0 && obj->low[i] > obj->low[i - 1]; i--) {
        int temp = obj->low[i];
        obj->low[i] = obj->low[i - 1];
        obj->low[i - 1] = temp;
    }

    if (obj->lowSize > 0 && obj->highSize > 0 && obj->low[0] > obj->high[0]) {
        int temp = obj->low[0];
        obj->low[0] = obj->high[0];
        obj->high[0] = temp;
    }

    if (obj->lowSize > obj->highSize + 1) {
        obj->high[obj->highSize++] = obj->low[--obj->lowSize];
        for (int i = obj->highSize - 1; i > 0 && obj->high[i] < obj->high[i - 1]; i--) {
            int temp = obj->high[i];
            obj->high[i] = obj->high[i - 1];
            obj->high[i - 1] = temp;
        }
    }
}

double findMedian(MedianFinder* obj) {
    if (obj->lowSize > obj->highSize) {
        return (double)obj->low[0];
    } else {
        return ((double)obj->low[0] + (double)obj->high[0]) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->low);
    free(obj->high);
    free(obj);
}

int main() {
    MedianFinder* medianFinder = medianFinderCreate();
    addNum(medianFinder, 1);
    addNum(medianFinder, 2);
    printf("%f\n", findMedian(medianFinder)); // Output: 1.5
    addNum(medianFinder, 3);
    printf("%f\n", findMedian(medianFinder)); // Output: 2.0
    addNum(medianFinder, 4);
    addNum(medianFinder, 5);
    printf("%f\n", findMedian(medianFinder)); // Output: 3.0
    medianFinderFree(medianFinder);

    return 0;
}