
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefixProducts;
    int size;
    int capacity;
} Task176;

Task176* task176Create() {
    Task176* obj = (Task176*)malloc(sizeof(Task176));
    obj->capacity = 16;
    obj->prefixProducts = (int*)malloc(obj->capacity * sizeof(int));
    obj->size = 1;
    obj->prefixProducts[0] = 1;
    return obj;
}

void task176Add(Task176* obj, int num) {
    if (num == 0) {
        obj->size = 1;
        obj->prefixProducts[0] = 1;
        return;
    }
    
    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->prefixProducts = (int*)realloc(obj->prefixProducts, obj->capacity * sizeof(int));
    }
    
    obj->prefixProducts[obj->size] = obj->prefixProducts[obj->size - 1] * num;
    obj->size++;
}

int task176GetProduct(Task176* obj, int k) {
    if (k >= obj->size) return 0;
    return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - k - 1];
}

void task176Free(Task176* obj) {
    free(obj->prefixProducts);
    free(obj);
}

int main() {
    // Test case 1
    Task176* t1 = task176Create();
    task176Add(t1, 3);
    task176Add(t1, 0);
    task176Add(t1, 2);
    task176Add(t1, 5);
    task176Add(t1, 4);
    printf("%d\\n", task176GetProduct(t1, 2)); // Expected: 20
    task176Free(t1);

    // Test case 2
    Task176* t2 = task176Create();
    task176Add(t2, 2);
    task176Add(t2, 3);
    task176Add(t2, 4);
    printf("%d\\n", task176GetProduct(t2, 3)); // Expected: 24
    task176Free(t2);

    // Test case 3
    Task176* t3 = task176Create();
    task176Add(t3, 1);
    task176Add(t3, 2);
    task176Add(t3, 3);
    task176Add(t3, 0);
    printf("%d\\n", task176GetProduct(t3, 2)); // Expected: 0
    task176Free(t3);

    // Test case 4
    Task176* t4 = task176Create();
    task176Add(t4, 5);
    task176Add(t4, 2);
    task176Add(t4, 4);
    task176Add(t4, 8);
    printf("%d\\n", task176GetProduct(t4, 2)); // Expected: 32
    task176Free(t4);

    // Test case 5
    Task176* t5 = task176Create();
    task176Add(t5, 3);
    task176Add(t5, 6);
    task176Add(t5, 0);
    task176Add(t5, 2);
    task176Add(t5, 4);
    printf("%d\\n", task176GetProduct(t5, 3)); // Expected: 0
    task176Free(t5);

    return 0;
}
