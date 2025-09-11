
#include <stdio.h>
#include <stdlib.h>

// Note: This is a simplified version for C as it doesn't have built-in heap data structure
#define MAX_SIZE 50000

typedef struct {
    int* nums;
    int size;
} Task195;

Task195* task195Create() {
    Task195* obj = (Task195*)malloc(sizeof(Task195));
    obj->nums = (int*)malloc(MAX_SIZE * sizeof(int));
    obj->size = 0;
    return obj;
}

void task195AddNum(Task195* obj, int num) {
    int i, j;
    // Insert number at correct position to maintain sorted array
    for (i = 0; i < obj->size; i++) {
        if (obj->nums[i] > num) break;
    }
    for (j = obj->size; j > i; j--) {
        obj->nums[j] = obj->nums[j-1];
    }
    obj->nums[i] = num;
    obj->size++;
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
    printf("%.1f\\n", task195FindMedian(mf1));  // Expected: 1.5
    
    // Test case 2
    task195AddNum(mf1, 3);
    printf("%.1f\\n", task195FindMedian(mf1));  // Expected: 2.0
    
    // Test case 3
    Task195* mf2 = task195Create();
    task195AddNum(mf2, 5);
    printf("%.1f\\n", task195FindMedian(mf2));  // Expected: 5.0
    
    // Test case 4
    Task195* mf3 = task195Create();
    task195AddNum(mf3, 1);
    task195AddNum(mf3, 2);
    task195AddNum(mf3, 3);
    task195AddNum(mf3, 4);
    printf("%.1f\\n", task195FindMedian(mf3));  // Expected: 2.5
    
    // Test case 5
    Task195* mf4 = task195Create();
    task195AddNum(mf4, -1);
    task195AddNum(mf4, -2);
    task195AddNum(mf4, -3);
    printf("%.1f\\n", task195FindMedian(mf4));  // Expected: -2.0
    
    // Free memory
    task195Free(mf1);
    task195Free(mf2);
    task195Free(mf3);
    task195Free(mf4);
    
    return 0;
}
