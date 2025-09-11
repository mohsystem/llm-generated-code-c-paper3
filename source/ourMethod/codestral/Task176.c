#include <stdlib.h>
#include <stdio.h>

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
            obj->products = (int*)realloc(obj->products, obj->capacity * sizeof(int));
        }
        obj->products[obj->size++] = obj->products[obj->size - 2] * num;
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
    ProductOfNumbers* pn = productOfNumbersCreate();
    productOfNumbersAdd(pn, 3);
    productOfNumbersAdd(pn, 0);
    productOfNumbersAdd(pn, 2);
    productOfNumbersAdd(pn, 5);
    productOfNumbersAdd(pn, 4);
    printf("%d\n", productOfNumbersGetProduct(pn, 2)); // 20
    printf("%d\n", productOfNumbersGetProduct(pn, 3)); // 40
    printf("%d\n", productOfNumbersGetProduct(pn, 4)); // 0
    productOfNumbersAdd(pn, 8);
    printf("%d\n", productOfNumbersGetProduct(pn, 2)); // 32
    productOfNumbersFree(pn);
    return 0;
}