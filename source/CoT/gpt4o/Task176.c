#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefixProducts;
    int size;
    int capacity;
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    obj->prefixProducts = (int*)malloc(sizeof(int) * 2);
    obj->prefixProducts[0] = 1;
    obj->size = 1;
    obj->capacity = 2;
    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
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

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - 1 - k];
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->prefixProducts);
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