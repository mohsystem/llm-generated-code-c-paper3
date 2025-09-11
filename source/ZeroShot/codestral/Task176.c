#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* prefixProducts;
    int size;
    int capacity;
} Task176;

Task176* Task176Create() {
    Task176* obj = (Task176*)malloc(sizeof(Task176));
    obj->size = 0;
    obj->capacity = 1;
    obj->prefixProducts = (int*)malloc(sizeof(int));
    obj->prefixProducts[0] = 1; // to handle the case when k = 1
    return obj;
}

void Task176Add(Task176* obj, int num) {
    if (num == 0) {
        obj->size = 1;
        obj->prefixProducts[0] = 1;
    } else {
        if (obj->size == obj->capacity) {
            obj->capacity *= 2;
            obj->prefixProducts = (int*)realloc(obj->prefixProducts, sizeof(int) * obj->capacity);
        }
        obj->prefixProducts[obj->size] = obj->prefixProducts[obj->size - 1] * num;
        obj->size++;
    }
}

int Task176GetProduct(Task176* obj, int k) {
    if (k > obj->size - 1) {
        return 0;
    } else {
        return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - k - 1];
    }
}

void Task176Free(Task176* obj) {
    free(obj->prefixProducts);
    free(obj);
}

int main() {
    Task176* productOfNumbers = Task176Create();
    Task176Add(productOfNumbers, 3);
    Task176Add(productOfNumbers, 0);
    Task176Add(productOfNumbers, 2);
    Task176Add(productOfNumbers, 5);
    Task176Add(productOfNumbers, 4);
    printf("%d\n", Task176GetProduct(productOfNumbers, 2)); // 20
    printf("%d\n", Task176GetProduct(productOfNumbers, 3)); // 40
    printf("%d\n", Task176GetProduct(productOfNumbers, 4)); // 0
    Task176Add(productOfNumbers, 8);
    printf("%d\n", Task176GetProduct(productOfNumbers, 2)); // 32
    Task176Free(productOfNumbers);
    return 0;
}