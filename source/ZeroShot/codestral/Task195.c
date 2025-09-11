#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *maxHeap;
    int maxHeapSize;
    int *minHeap;
    int minHeapSize;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*) malloc(sizeof(MedianFinder));
    obj->maxHeap = (int*) malloc(sizeof(int) * 100000);
    obj->minHeap = (int*) malloc(sizeof(int) * 100000);
    obj->maxHeapSize = 0;
    obj->minHeapSize = 0;
    return obj;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void insert(int arr[], int *n, int key) {
    (*n)++;
    int i = *n - 1;
    arr[i] = key;

    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMax(int arr[], int *n) {
    int root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return root;
}

void heapifyMin(int arr[], int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] < arr[smallest])
        smallest = l;

    if (r < n && arr[r] < arr[smallest])
        smallest = r;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapifyMin(arr, n, smallest);
    }
}

void insertMin(int arr[], int *n, int key) {
    (*n)++;
    int i = *n - 1;
    arr[i] = key;

    while (i != 0 && arr[(i - 1) / 2] > arr[i]) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(int arr[], int *n) {
    int root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapifyMin(arr, *n, 0);
    return root;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    insert(obj->maxHeap, &(obj->maxHeapSize), num);
    insertMin(obj->minHeap, &(obj->minHeapSize), extractMax(obj->maxHeap, &(obj->maxHeapSize)));
    if (obj->maxHeapSize < obj->minHeapSize) {
        insert(obj->maxHeap, &(obj->maxHeapSize), extractMin(obj->minHeap, &(obj->minHeapSize)));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
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
    MedianFinder* obj = medianFinderCreate();
    medianFinderAddNum(obj, 1);
    medianFinderAddNum(obj, 2);
    printf("%f\n", medianFinderFindMedian(obj));  // returns 1.5
    medianFinderAddNum(obj, 3);
    printf("%f\n", medianFinderFindMedian(obj));  // returns 2.0
    medianFinderFree(obj);
    return 0;
}