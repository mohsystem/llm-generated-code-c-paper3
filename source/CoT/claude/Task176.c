
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
    Task176* prod = task176Create();
    task176Add(prod, 3);
    task176Add(prod, 0);
    task176Add(prod, 2);
    task176Add(prod, 5);
    task176Add(prod, 4);
    printf("%d\\n", task176GetProduct(prod, 2));  // Should print 20
    task176Free(prod);
    
    // Test case 2
    Task176* prod2 = task176Create();
    task176Add(prod2, 2);
    task176Add(prod2, 3);
    task176Add(prod2, 4);
    printf("%d\\n", task176GetProduct(prod2, 3));  // Should print 24
    task176Free(prod2);
    
    // Test case 3
    Task176* prod3 = task176Create();
    task176Add(prod3, 1);
    task176Add(prod3, 1);
    task176Add(prod3, 1);
    printf("%d\\n", task176GetProduct(prod3, 2));  // Should print 1
    task176Free(prod3);
    
    // Test case 4
    Task176* prod4 = task176Create();
    task176Add(prod4, 10);
    task176Add(prod4, 0);
    task176Add(prod4, 2);
    printf("%d\\n", task176GetProduct(prod4, 2));  // Should print 0
    task176Free(prod4);
    
    // Test case 5
    Task176* prod5 = task176Create();
    task176Add(prod5, 5);
    task176Add(prod5, 2);
    task176Add(prod5, 4);
    task176Add(prod5, 3);
    printf("%d\\n", task176GetProduct(prod5, 3));  // Should print 24
    task176Free(prod5);
    
    return 0;
}
