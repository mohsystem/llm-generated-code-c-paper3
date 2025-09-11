#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *lowerHalf;
    int lowerSize;
    int lowerCapacity;
    int *upperHalf;
    int upperSize;
    int upperCapacity;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));
    obj->lowerCapacity = 10;
    obj->lowerSize = 0;
    obj->lowerHalf = (int *)malloc(sizeof(int) * obj->lowerCapacity);
    obj->upperCapacity = 10;
    obj->upperSize = 0;
    obj->upperHalf = (int *)malloc(sizeof(int) * obj->upperCapacity);
    return obj;
}

void addNum(MedianFinder* obj, int num) {
    if (obj->lowerSize == obj->lowerCapacity) {
        obj->lowerCapacity *= 2;
        obj->lowerHalf = (int *)realloc(obj->lowerHalf, sizeof(int) * obj->lowerCapacity);
    }
    if (obj->upperSize == obj->upperCapacity) {
        obj->upperCapacity *= 2;
        obj->upperHalf = (int *)realloc(obj->upperHalf, sizeof(int) * obj->upperCapacity);
    }
    obj->lowerHalf[obj->lowerSize++] = num;

    for (int i = obj->lowerSize - 1; i > 0; --i) {
        if (obj->lowerHalf[i] > obj->lowerHalf[i - 1]) {
            int temp = obj->lowerHalf[i];
            obj->lowerHalf[i] = obj->lowerHalf[i - 1];
            obj->lowerHalf[i - 1] = temp;
        }
    }

    obj->upperHalf[obj->upperSize++] = obj->lowerHalf[--obj->lowerSize];

    for (int i = obj->upperSize - 1; i > 0; --i) {
        if (obj->upperHalf[i] < obj->upperHalf[i - 1]) {
            int temp = obj->upperHalf[i];
            obj->upperHalf[i] = obj->upperHalf[i - 1];
            obj->upperHalf[i - 1] = temp;
        }
    }

    if (obj->lowerSize < obj->upperSize) {
        obj->lowerHalf[obj->lowerSize++] = obj->upperHalf[--obj->upperSize];
    }
}

double findMedian(MedianFinder* obj) {
    if (obj->lowerSize == obj->upperSize) {
        return (obj->lowerHalf[obj->lowerSize - 1] + obj->upperHalf[obj->upperSize - 1]) / 2.0;
    } else {
        return obj->lowerHalf[obj->lowerSize - 1];
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->lowerHalf);
    free(obj->upperHalf);
    free(obj);
}

int main() {
    MedianFinder* medianFinder = medianFinderCreate();
    addNum(medianFinder, 1);
    addNum(medianFinder, 2);
    printf("%f\n", findMedian(medianFinder)); // 1.5
    addNum(medianFinder, 3);
    printf("%f\n", findMedian(medianFinder)); // 2.0
    addNum(medianFinder, 4);
    printf("%f\n", findMedian(medianFinder)); // 2.5
    addNum(medianFinder, 5);
    printf("%f\n", findMedian(medianFinder)); // 3.0
    medianFinderFree(medianFinder);
    return 0;
}