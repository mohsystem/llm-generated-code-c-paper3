#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* products;
    int size;
    int capacity;
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    obj->products = (int*)malloc(sizeof(int));
    obj->products[0] = 1;
    obj->size = 1;
    obj->capacity = 1;
    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 1;
        obj->products[0] = 1;
    } else {
        if (obj->size == obj->capacity) {
            obj->capacity *= 2;
            obj->products = (int*)realloc(obj->products, sizeof(int) * obj->capacity);
        }
        obj->products[obj->size] = obj->products[obj->size - 1] * num;
        obj->size++;
    }
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    if (k >= obj->size) {
        return 0;
    }
    return obj->products[obj->size - 1] / obj->products[obj->size - k - 1];
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->products);
    free(obj);
}

int main() {
    ProductOfNumbers* productOfNumbers = productOfNumbersCreate();
    productOfNumbersAdd(productOfNumbers, 3);
    productOfNumbersAdd(productOfNumbers, 0);
    productOfNumbersAdd(productOfNumbers, 2);
    productOfNumbersAdd(productOfNumbers, 5);
    productOfNumbersAdd(productOfNumbers, 4);
    printf("%d\n", productOfNumbersGetProduct(productOfNumbers, 2)); // 20
    printf("%d\n", productOfNumbersGetProduct(productOfNumbers, 3)); // 40
    printf("%d\n", productOfNumbersGetProduct(productOfNumbers, 4)); // 0
    productOfNumbersAdd(productOfNumbers, 8);
    printf("%d\n", productOfNumbersGetProduct(productOfNumbers, 2)); // 32
    productOfNumbersFree(productOfNumbers);
    return 0;
}