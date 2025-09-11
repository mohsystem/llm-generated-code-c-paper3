#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* minHeap;
    int* maxHeap;
    int minHeapSize;
    int maxHeapSize;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = malloc(sizeof(MedianFinder));
    obj->minHeap = malloc(sizeof(int) * 50000);
    obj->maxHeap = malloc(sizeof(int) * 50000);
    obj->minHeapSize = 0;
    obj->maxHeapSize = 0;
    return obj;
}

void addNum(MedianFinder* obj, int num) {
    if (obj->maxHeapSize == 0 || num < obj->maxHeap[0]) {
        obj->maxHeap[obj->maxHeapSize++] = num;
    } else {
        obj->minHeap[obj->minHeapSize++] = num;
    }
    rebalanceHeaps(obj);
}

double findMedian(MedianFinder* obj) {
    if (obj->maxHeapSize == obj->minHeapSize) {
        return (obj->maxHeap[0] + obj->minHeap[0]) / 2.0;
    } else {
        return obj->maxHeap[0];
    }
}

void rebalanceHeaps(MedianFinder* obj) {
    if (obj->maxHeapSize > obj->minHeapSize + 1) {
        obj->minHeap[obj->minHeapSize++] = obj->maxHeap[0];
        obj->maxHeap[0] = obj->maxHeap[--obj->maxHeapSize];
    } else if (obj->minHeapSize > obj->maxHeapSize) {
        obj->maxHeap[obj->maxHeapSize++] = obj->minHeap[0];
        obj->minHeap[0] = obj->minHeap[--obj->minHeapSize];
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->minHeap);
    free(obj->maxHeap);
    free(obj);
}