#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *heap;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity, int isMinHeap) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->heap = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void pushHeap(Heap* heap, int isMinHeap, int num) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->heap = (int*)realloc(heap->heap, sizeof(int) * heap->capacity);
    }

    heap->heap[heap->size] = num;
    int i = heap->size++;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if ((isMinHeap && heap->heap[parent] > heap->heap[i]) || (!isMinHeap && heap->heap[parent] < heap->heap[i])) {
            int temp = heap->heap[parent];
            heap->heap[parent] = heap->heap[i];
            heap->heap[i] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

int popHeap(Heap* heap, int isMinHeap) {
    int num = heap->heap[0];
    heap->heap[0] = heap->heap[--heap->size];

    int i = 0;
    while (i < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && ((isMinHeap && heap->heap[left] < heap->heap[smallest]) || (!isMinHeap && heap->heap[left] > heap->heap[smallest]))) {
            smallest = left;
        }

        if (right < heap->size && ((isMinHeap && heap->heap[right] < heap->heap[smallest]) || (!isMinHeap && heap->heap[right] > heap->heap[smallest]))) {
            smallest = right;
        }

        if (smallest != i) {
            int temp = heap->heap[smallest];
            heap->heap[smallest] = heap->heap[i];
            heap->heap[i] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return num;
}

typedef struct {
    Heap* minHeap;
    Heap* maxHeap;
} MedianFinder;

MedianFinder* createMedianFinder() {
    MedianFinder* medianFinder = (MedianFinder*)malloc(sizeof(MedianFinder));
    medianFinder->minHeap = createHeap(100, 1);
    medianFinder->maxHeap = createHeap(100, 0);
    return medianFinder;
}

void addNum(MedianFinder* medianFinder, int num) {
    if (medianFinder->maxHeap->size == 0 || num < medianFinder->maxHeap->heap[0]) {
        pushHeap(medianFinder->maxHeap, 0, num);
    } else {
        pushHeap(medianFinder->minHeap, 1, num);
    }

    if (medianFinder->maxHeap->size > medianFinder->minHeap->size + 1) {
        pushHeap(medianFinder->minHeap, 1, popHeap(medianFinder->maxHeap, 0));
    } else if (medianFinder->minHeap->size > medianFinder->maxHeap->size) {
        pushHeap(medianFinder->maxHeap, 0, popHeap(medianFinder->minHeap, 1));
    }
}

double findMedian(MedianFinder* medianFinder) {
    if (medianFinder->maxHeap->size == medianFinder->minHeap->size) {
        return (medianFinder->maxHeap->heap[0] + medianFinder->minHeap->heap[0]) / 2.0;
    } else {
        return medianFinder->maxHeap->heap[0];
    }
}

int main() {
    MedianFinder* medianFinder = createMedianFinder();
    addNum(medianFinder, 1);
    addNum(medianFinder, 2);
    printf("%f\n", findMedian(medianFinder)); // Output: 1.5
    addNum(medianFinder, 3);
    printf("%f\n", findMedian(medianFinder)); // Output: 2.0
    return 0;
}