
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefix;
    int size;
    int capacity;
} Task176;

Task176* task176Create() {
    Task176* obj = (Task176*)malloc(sizeof(Task176));
    obj->capacity = 16;
    obj->prefix = (int*)malloc(obj->capacity * sizeof(int));
    obj->size = 1;
    obj->prefix[0] = 1;
    return obj;
}

void task176Add(Task176* obj, int num) {
    if (num == 0) {
        obj->size = 1;
        obj->prefix[0] = 1;
    } else {
        if (obj->size == obj->capacity) {
            obj->capacity *= 2;
            obj->prefix = (int*)realloc(obj->prefix, obj->capacity * sizeof(int));
        }
        obj->prefix[obj->size] = obj->prefix[obj->size - 1] * num;
        obj->size++;
    }
}

int task176GetProduct(Task176* obj, int k) {
    if (k >= obj->size) return 0;
    return obj->prefix[obj->size - 1] / obj->prefix[obj->size - k - 1];
}

void task176Free(Task176* obj) {
    free(obj->prefix);
    free(obj);
}

int main() {
    // Test case 1
    Task176* p1 = task176Create();
    task176Add(p1, 3);
    task176Add(p1, 0);
    task176Add(p1, 2);
    printf("%d\\n", task176GetProduct(p1, 2));  // Should print 0
    task176Free(p1);

    // Test case 2
    Task176* p2 = task176Create();
    task176Add(p2, 2);
    task176Add(p2, 3);
    task176Add(p2, 4);
    printf("%d\\n", task176GetProduct(p2, 3));  // Should print 24
    task176Free(p2);

    // Test case 3
    Task176* p3 = task176Create();
    task176Add(p3, 5);
    task176Add(p3, 2);
    printf("%d\\n", task176GetProduct(p3, 2));  // Should print 10
    task176Free(p3);

    // Test case 4
    Task176* p4 = task176Create();
    task176Add(p4, 3);
    task176Add(p4, 1);
    task176Add(p4, 2);
    task176Add(p4, 5);
    task176Add(p4, 4);
    printf("%d\\n", task176GetProduct(p4, 2));  // Should print 20
    task176Free(p4);

    // Test case 5
    Task176* p5 = task176Create();
    task176Add(p5, 1);
    task176Add(p5, 1);
    task176Add(p5, 1);
    printf("%d\\n", task176GetProduct(p5, 3));  // Should print 1
    task176Free(p5);

    return 0;
}
