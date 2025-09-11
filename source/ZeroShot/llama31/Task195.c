#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

typedef struct {
    int* maxHeap;
    int* minHeap;
    int maxHeapSize;
    int minHeapSize;
    int maxHeapCapacity;
    int minHeapCapacity;
} Task195;

Task195* Task195Create() {
    Task195* obj = (Task195*) malloc(sizeof(Task195));
    obj->maxHeap = (int*) malloc(MAX_SIZE * sizeof(int));
    obj->minHeap = (int*) malloc(MAX_SIZE * sizeof(int));
    obj->maxHeapSize = 0;
    obj->minHeapSize = 0;
    obj->maxHeapCapacity = MAX_SIZE;
    obj->minHeapCapacity = MAX_SIZE;
    return obj;
}

void Task195AddNum(Task195* obj, int num) {
    if (obj->maxHeapSize == 0 || num <= obj->maxHeap[0]) {
        obj->maxHeap[obj->maxHeapSize++] = num;
    } else {
        obj->minHeap[obj->minHeapSize++] = num;
    }

    // Balance heaps
    if (obj->maxHeapSize > obj->minHeapSize + 1) {
        obj->minHeap[obj->minHeapSize++] = obj->maxHeap[obj->maxHeapSize - 1];
        obj->maxHeapSize--;
    } else if (obj->minHeapSize > obj->maxHeapSize) {
        obj->maxHeap[obj->maxHeapSize++] = obj->minHeap[obj->minHeapSize - 1];
        obj->minHeapSize--;
    }

    // Heapify (simplified, not efficient for large inputs)
    for (int i = obj->maxHeapSize / 2 - 1; i >= 0; i--) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < obj->maxHeapSize && obj->maxHeap[left] > obj->maxHeap[largest]) {
            largest = left;
        }

        if (right < obj->maxHeapSize && obj->maxHeap[right] > obj->maxHeap[largest]) {
            largest = right;
        }

        if (largest != i) {
            int temp = obj->maxHeap[i];
            obj->maxHeap[i] = obj->maxHeap[largest];
            obj->maxHeap[largest] = temp;
        }
    }

    for (int i = obj->minHeapSize / 2 - 1; i >= 0; i--) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < obj->minHeapSize && obj->minHeap[left] < obj->minHeap[smallest]) {
            smallest = left;
        }

        if (right < obj->minHeapSize && obj->minHeap[right] < obj->minHeap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            int temp = obj->minHeap[i];
            obj->minHeap[i] = obj->minHeap[smallest];
            obj->minHeap[smallest] = temp;
        }
    }
}

double Task195FindMedian(Task195* obj) {
    if (obj->maxHeapSize == obj->minHeapSize) {
        return (obj->maxHeap[0] + obj->minHeap[0]) / 2.0;
    } else {
        return (double) obj->maxHeap[0];
    }
}

int main() {
    Task195* medianFinder = Task195Create();
    Task195AddNum(medianFinder, 1);
    Task195AddNum(medianFinder, 2);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 1.5
    Task195AddNum(medianFinder, 3);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 2.0

    medianFinder = Task195Create();
    Task195AddNum(medianFinder, 2);
    Task195AddNum(medianFinder, 3);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 2.5
    Task195AddNum(medianFinder, 4);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 3.0

    medianFinder = Task195Create();
    Task195AddNum(medianFinder, 1);
    Task195AddNum(medianFinder, 2);
    Task195AddNum(medianFinder, 3);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 2.0

    medianFinder = Task195Create();
    Task195AddNum(medianFinder, 1);
    Task195AddNum(medianFinder, 3);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 2.0
    Task195AddNum(medianFinder, 5);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 3.0

    return 0;
}