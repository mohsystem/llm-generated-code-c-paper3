#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* maxHeap;
    int* minHeap;
    int maxHeapSize;
    int minHeapSize;
    int maxHeapCapacity;
    int minHeapCapacity;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->maxHeap = (int*)malloc(50000 * sizeof(int));
    obj->minHeap = (int*)malloc(50000 * sizeof(int));
    obj->maxHeapSize = 0;
    obj->minHeapSize = 0;
    obj->maxHeapCapacity = 50000;
    obj->minHeapCapacity = 50000;
    return obj;
}

void heapifyDownMax(int* heap, int size, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < size && heap[left] > heap[largest]) largest = left;
    if (right < size && heap[right] > heap[largest]) largest = right;
    if (largest != idx) {
        int temp = heap[idx];
        heap[idx] = heap[largest];
        heap[largest] = temp;
        heapifyDownMax(heap, size, largest);
    }
}

void heapifyDownMin(int* heap, int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;
    if (smallest != idx) {
        int temp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = temp;
        heapifyDownMin(heap, size, smallest);
    }
}

void heapifyUpMax(int* heap, int idx) {
    int parent = (idx - 1) / 2;
    if (parent >= 0 && heap[parent] < heap[idx]) {
        int temp = heap[parent];
        heap[parent] = heap[idx];
        heap[idx] = temp;
        heapifyUpMax(heap, parent);
    }
}

void heapifyUpMin(int* heap, int idx) {
    int parent = (idx - 1) / 2;
    if (parent >= 0 && heap[parent] > heap[idx]) {
        int temp = heap[parent];
        heap[parent] = heap[idx];
        heap[idx] = temp;
        heapifyUpMin(heap, parent);
    }
}

void addNum(MedianFinder* obj, int num) {
    obj->maxHeap[obj->maxHeapSize++] = num;
    heapifyUpMax(obj->maxHeap, obj->maxHeapSize - 1);
    
    obj->minHeap[obj->minHeapSize++] = obj->maxHeap[0];
    obj->maxHeap[0] = obj->maxHeap[--obj->maxHeapSize];
    heapifyDownMax(obj->maxHeap, obj->maxHeapSize, 0);
    heapifyUpMin(obj->minHeap, obj->minHeapSize - 1);
    
    if (obj->maxHeapSize < obj->minHeapSize) {
        obj->maxHeap[obj->maxHeapSize++] = obj->minHeap[0];
        obj->minHeap[0] = obj->minHeap[--obj->minHeapSize];
        heapifyDownMin(obj->minHeap, obj->minHeapSize, 0);
        heapifyUpMax(obj->maxHeap, obj->maxHeapSize - 1);
    }
}

double findMedian(MedianFinder* obj) {
    if (obj->maxHeapSize > obj->minHeapSize) {
        return obj->maxHeap[0];
    } else {
        return (obj->maxHeap[0] + obj->minHeap[0]) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->maxHeap);
    free(obj->minHeap);
    free(obj);
}

int main() {
    MedianFinder* medianFinder = medianFinderCreate();
    addNum(medianFinder, 1);
    addNum(medianFinder, 2);
    printf("%lf\n", findMedian(medianFinder)); // 1.5
    addNum(medianFinder, 3);
    printf("%lf\n", findMedian(medianFinder)); // 2.0
    addNum(medianFinder, 4);
    printf("%lf\n", findMedian(medianFinder)); // 2.5
    addNum(medianFinder, 5);
    printf("%lf\n", findMedian(medianFinder)); // 3.0
    medianFinderFree(medianFinder);
    return 0;
}