#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *prefixProducts;
    int size;
    int capacity;
} ProductOfNumbers;

ProductOfNumbers* ProductOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    obj->capacity = 10;
    obj->prefixProducts = (int*)malloc(sizeof(int) * obj->capacity);
    obj->prefixProducts[0] = 1;
    obj->size = 1;
    return obj;
}

void ProductOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 1;
    } else {
        if (obj->size == obj->capacity) {
            obj->capacity *= 2;
            obj->prefixProducts = (int*)realloc(obj->prefixProducts, sizeof(int) * obj->capacity);
        }
        obj->prefixProducts[obj->size] = obj->prefixProducts[obj->size - 1] * num;
        obj->size++;
    }
}

int ProductOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - 1 - k];
}

void ProductOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->prefixProducts);
    free(obj);
}

int main() {
    ProductOfNumbers* productOfNumbers = ProductOfNumbersCreate();
    ProductOfNumbersAdd(productOfNumbers, 3);
    ProductOfNumbersAdd(productOfNumbers, 0);
    ProductOfNumbersAdd(productOfNumbers, 2);
    ProductOfNumbersAdd(productOfNumbers, 5);
    ProductOfNumbersAdd(productOfNumbers, 4);
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 2)); // 20
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 3)); // 40
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 4)); // 0
    ProductOfNumbersAdd(productOfNumbers, 8);
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 2)); // 32
    ProductOfNumbersFree(productOfNumbers);
    return 0;
}