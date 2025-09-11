
#include <stdio.h>
#include <stdlib.h>

// Simple array-based implementation since C doesn't have priority queue
typedef struct {
    int* nums;
    int size;
    int capacity;
} Task195;

Task195* createMedianFinder() {
    Task195* obj = (Task195*)malloc(sizeof(Task195));
    obj->capacity = 100;
    obj->nums = (int*)malloc(obj->capacity * sizeof(int));
    obj->size = 0;
    return obj;
}

void addNum(Task195* obj, int num) {
    if(obj->size >= obj->capacity) {
        obj->capacity *= 2;
        obj->nums = realloc(obj->nums, obj->capacity * sizeof(int));
    }
    
    // Insert and maintain sorted order
    int i = obj->size - 1;
    while(i >= 0 && obj->nums[i] > num) {
        obj->nums[i+1] = obj->nums[i];
        i--;
    }
    obj->nums[i+1] = num;
    obj->size++;
}

double findMedian(Task195* obj) {
    if(obj->size % 2 == 1) {
        return obj->nums[obj->size/2];
    }
    return (obj->nums[obj->size/2-1] + obj->nums[obj->size/2]) / 2.0;
}

void freeMedianFinder(Task195* obj) {
    free(obj->nums);
    free(obj);
}

int main() {
    // Test case 1
    Task195* mf = createMedianFinder();
    addNum(mf, 1);
    addNum(mf, 2);
    printf("%.1f\\n", findMedian(mf)); // 1.5
    
    // Test case 2
    addNum(mf, 3);
    printf("%.1f\\n", findMedian(mf)); // 2.0
    
    // Test case 3
    Task195* mf2 = createMedianFinder();
    addNum(mf2, 5);
    printf("%.1f\\n", findMedian(mf2)); // 5.0
    
    // Test case 4
    addNum(mf2, 4);
    addNum(mf2, 3);
    printf("%.1f\\n", findMedian(mf2)); // 4.0
    
    // Test case 5
    addNum(mf2, 2);
    addNum(mf2, 1);
    printf("%.1f\\n", findMedian(mf2)); // 3.0
    
    freeMedianFinder(mf);
    freeMedianFinder(mf2);
    
    return 0;
}
