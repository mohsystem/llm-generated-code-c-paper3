#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefixProducts;
    int size;
    int capacity;
} Task176;

Task176* Task176Create() {
    Task176* obj = (Task176*) malloc(sizeof(Task176));
    obj->prefixProducts = (int*) malloc(40001 * sizeof(int));
    obj->size = 0;
    obj->capacity = 40001;
    obj->prefixProducts[0] = 1;
    return obj;
}

void add(Task176* obj, int num) {
    if (num == 0) {
        obj->size = 0;
        obj->prefixProducts[0] = 1;
    } else {
        if (obj->size == 0) {
            obj->prefixProducts[0] = num;
        } else {
            obj->prefixProducts[obj->size] = obj->prefixProducts[obj->size - 1] * num;
        }
        obj->size++;
    }
}

int getProduct(Task176* obj, int k) {
    if (obj->size < k) {
        return 0;
    }
    if (obj->size - k - 1 < 0) {
        return obj->prefixProducts[obj->size - 1];
    }
    return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - k - 1];
}

int main() {
    Task176* productOfNumbers = Task176Create();
    add(productOfNumbers, 3);
    add(productOfNumbers, 0);
    add(productOfNumbers, 2);
    add(productOfNumbers, 5);
    add(productOfNumbers, 4);
    printf("%d\n", getProduct(productOfNumbers, 2));  // Output: 20
    printf("%d\n", getProduct(productOfNumbers, 3));  // Output: 40
    printf("%d\n", getProduct(productOfNumbers, 4));  // Output: 0
    add(productOfNumbers, 8);
    printf("%d\n", getProduct(productOfNumbers, 2));  // Output: 32
    free(productOfNumbers->prefixProducts);
    free(productOfNumbers);
    return 0;
}