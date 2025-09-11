#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *minHeap;
    int *maxHeap;
    int minSize;
    int maxSize;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder *mf = (MedianFinder *)malloc(sizeof(MedianFinder));
    mf->minHeap = (int *)malloc(sizeof(int) * 50000);
    mf->maxHeap = (int *)malloc(sizeof(int) * 50000);
    mf->minSize = 0;
    mf->maxSize = 0;
    return mf;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUpMin(int *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyUpMax(int *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDownMin(int *heap, int size, int index) {
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swap(&heap[index], &heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void heapifyDownMax(int *heap, int size, int index) {
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(&heap[index], &heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->minSize == 0 || num > obj->minHeap[0]) {
        obj->minHeap[obj->minSize++] = num;
        heapifyUpMin(obj->minHeap, obj->minSize - 1);
    } else {
        obj->maxHeap[obj->maxSize++] = num;
        heapifyUpMax(obj->maxHeap, obj->maxSize - 1);
    }

    if (obj->minSize > obj->maxSize + 1) {
        obj->maxHeap[obj->maxSize++] = obj->minHeap[0];
        obj->minHeap[0] = obj->minHeap[--obj->minSize];
        heapifyDownMin(obj->minHeap, obj->minSize, 0);
        heapifyUpMax(obj->maxHeap, obj->maxSize - 1);
    } else if (obj->maxSize > obj->minSize) {
        obj->minHeap[obj->minSize++] = obj->maxHeap[0];
        obj->maxHeap[0] = obj->maxHeap[--obj->maxSize];
        heapifyDownMax(obj->maxHeap, obj->maxSize, 0);
        heapifyUpMin(obj->minHeap, obj->minSize - 1);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->minSize == obj->maxSize) {
        return (obj->minHeap[0] + obj->maxHeap[0]) / 2.0;
    } else {
        return obj->minHeap[0];
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->minHeap);
    free(obj->maxHeap);
    free(obj);
}

int main() {
    MedianFinder* medianFinder = medianFinderCreate();
    medianFinderAddNum(medianFinder, 1);
    medianFinderAddNum(medianFinder, 2);
    printf("%f\n", medianFinderFindMedian(medianFinder)); // 1.5
    medianFinderAddNum(medianFinder, 3);
    printf("%f\n", medianFinderFindMedian(medianFinder)); // 2.0
    medianFinderFree(medianFinder);
    return 0;
}