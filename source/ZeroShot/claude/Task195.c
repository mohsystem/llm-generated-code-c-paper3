
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int size;
    int capacity;
} Task195;

Task195* task195Create() {
    Task195* obj = (Task195*)malloc(sizeof(Task195));
    obj->capacity = 16;
    obj->arr = (int*)malloc(sizeof(int) * obj->capacity);
    obj->size = 0;
    return obj;
}

void task195AddNum(Task195* obj, int num) {
    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = (int*)realloc(obj->arr, sizeof(int) * obj->capacity);
    }
    
    // Insert and maintain sorted order
    int i = obj->size - 1;
    while (i >= 0 && obj->arr[i] > num) {
        obj->arr[i + 1] = obj->arr[i];
        i--;
    }
    obj->arr[i + 1] = num;
    obj->size++;
}

double task195FindMedian(Task195* obj) {
    if (obj->size % 2 == 0) {
        return (obj->arr[obj->size/2 - 1] + obj->arr[obj->size/2]) / 2.0;
    }
    return obj->arr[obj->size/2];
}

void task195Free(Task195* obj) {
    free(obj->arr);
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
    task195AddNum(mf3, -1);
    task195AddNum(mf3, -2);
    task195AddNum(mf3, -3);
    printf("%.1f\\n", task195FindMedian(mf3));  // Expected: -2.0
    
    // Test case 5
    Task195* mf4 = task195Create();
    task195AddNum(mf4, 1);
    task195AddNum(mf4, 2);
    task195AddNum(mf4, 3);
    task195AddNum(mf4, 4);
    printf("%.1f\\n", task195FindMedian(mf4));  // Expected: 2.5
    
    // Free memory
    task195Free(mf1);
    task195Free(mf2);
    task195Free(mf3);
    task195Free(mf4);
    
    return 0;
}
