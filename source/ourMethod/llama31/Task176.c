#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefixProducts;
    int* zeroIndices;
    int prefixSize;
    int zeroSize;
} Task176;

Task176* Task176Create() {
    Task176* obj = (Task176*)malloc(sizeof(Task176));
    obj->prefixProducts = NULL;
    obj->zeroIndices = NULL;
    obj->prefixSize = 0;
    obj->zeroSize = 0;
    return obj;
}

void Task176Add(Task176* obj, int num) {
    if (num == 0) {
        obj->zeroIndices = (int*)realloc(obj->zeroIndices, (obj->zeroSize + 1) * sizeof(int));
        obj->zeroIndices[obj->zeroSize++] = obj->prefixSize;
        obj->prefixProducts = (int*)realloc(obj->prefixProducts, (obj->prefixSize + 1) * sizeof(int));
        obj->prefixProducts[obj->prefixSize++] = 1;
    } else {
        if (obj->prefixSize == 0) {
            obj->prefixProducts = (int*)realloc(obj->prefixProducts, (obj->prefixSize + 1) * sizeof(int));
            obj->prefixProducts[obj->prefixSize++] = num;
        } else {
            obj->prefixProducts = (int*)realloc(obj->prefixProducts, (obj->prefixSize + 1) * sizeof(int));
            obj->prefixProducts[obj->prefixSize++] = obj->prefixProducts[obj->prefixSize - 1] * num;
        }
    }
}

int Task176GetProduct(Task176* obj, int k) {
    if (k > obj->prefixSize) {
        return 0; // This should not happen based on the problem constraints
    }

    int lastIndex = obj->prefixSize - k;
    for (int i = 0; i < obj->zeroSize; i++) {
        if (obj->zeroIndices[i] == lastIndex) {
            return 0;
        }
    }

    if (lastIndex == 0) {
        return obj->prefixProducts[obj->prefixSize - 1];
    }
    return obj->prefixProducts[obj->prefixSize - 1] / obj->prefixProducts[lastIndex - 1];
}

int main() {
    Task176* productOfNumbers = Task176Create();
    Task176Add(productOfNumbers, 3);
    Task176Add(productOfNumbers, 0);
    Task176Add(productOfNumbers, 2);
    Task176Add(productOfNumbers, 5);
    Task176Add(productOfNumbers, 4);
    printf("%d\n", Task176GetProduct(productOfNumbers, 2)); // Output: 20
    printf("%d\n", Task176GetProduct(productOfNumbers, 3)); // Output: 40
    printf("%d\n", Task176GetProduct(productOfNumbers, 4)); // Output: 0
    Task176Add(productOfNumbers, 8);
    printf("%d\n", Task176GetProduct(productOfNumbers, 2)); // Output: 32
    free(productOfNumbers->prefixProducts);
    free(productOfNumbers->zeroIndices);
    free(productOfNumbers);
    return 0;
}