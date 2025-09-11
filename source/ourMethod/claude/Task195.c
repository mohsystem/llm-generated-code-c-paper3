
#include <stdio.h>
#include <stdlib.h>

// Simple implementation using array and sorting
typedef struct {
    int* nums;
    int size;
    int capacity;
} Task195;

Task195* task195Create() {
    Task195* obj = (Task195*)malloc(sizeof(Task195));
    obj->capacity = 50000;
    obj->nums = (int*)malloc(sizeof(int) * obj->capacity);
    obj->size = 0;
    return obj;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void task195AddNum(Task195* obj, int num) {
    if (obj->size < obj->capacity) {
        obj->nums[obj->size++] = num;
        qsort(obj->nums, obj->size, sizeof(int), compare);
    }
}

double task195FindMedian(Task195* obj) {
    if (obj->size % 2 == 0) {
        return (obj->nums[obj->size/2 - 1] + obj->nums[obj->size/2]) / 2.0;
    }
    return obj->nums[obj->size/2];
}

void task195Free(Task195* obj) {
    free(obj->nums);
    free(obj);
}

int main() {
    // Test case 1
    Task195* mf1 = task195Create();
    task195AddNum(mf1, 1);
    task195AddNum(mf1, 2);
    printf("%.1f\\n", task195FindMedian(mf1));  // 1.5
    task195Free(mf1);
    
    // Test case 2
    Task195* mf2 = task195Create();
    task195AddNum(mf2, 1);
    printf("%.1f\\n", task195FindMedian(mf2));  // 1.0
    task195Free(mf2);
    
    // Test case 3
    Task195* mf3 = task195Create();
    task195AddNum(mf3, 1);
    task195AddNum(mf3, 2);
    task195AddNum(mf3, 3);
    printf("%.1f\\n", task195FindMedian(mf3));  // 2.0
    task195Free(mf3);
    
    // Test case 4
    Task195* mf4 = task195Create();
    task195AddNum(mf4, 4);
    task195AddNum(mf4, 2);
    task195AddNum(mf4, 3);
    task195AddNum(mf4, 1);
    printf("%.1f\\n", task195FindMedian(mf4));  // 2.5
    task195Free(mf4);
    
    // Test case 5
    Task195* mf5 = task195Create();
    task195AddNum(mf5, 5);
    task195AddNum(mf5, 4);
    task195AddNum(mf5, 3);
    task195AddNum(mf5, 2);
    task195AddNum(mf5, 1);
    printf("%.1f\\n", task195FindMedian(mf5));  // 3.0
    task195Free(mf5);
    
    return 0;
}
