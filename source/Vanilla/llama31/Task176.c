#include <stdio.h>
#include <stdlib.h>

typedef struct ProductOfNumbers {
    int* prefix_products;
    int size;
    int capacity;
} ProductOfNumbers;

ProductOfNumbers* ProductOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    obj->capacity = 1;
    obj->size = 1;
    obj->prefix_products = (int*)malloc(sizeof(int) * obj->capacity);
    obj->prefix_products[0] = 1;
    return obj;
}

void add(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 1;
        obj->prefix_products[0] = 1;
        return;
    }
    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->prefix_products = (int*)realloc(obj->prefix_products, sizeof(int) * obj->capacity);
    }
    obj->prefix_products[obj->size] = obj->prefix_products[obj->size - 1] * num;
    obj->size++;
}

int getProduct(ProductOfNumbers* obj, int k) {
    if (obj->size <= k) {
        return 0;
    } else {
        return obj->prefix_products[obj->size - 1] / obj->prefix_products[obj->size - k - 1];
    }
}

void ProductOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->prefix_products);
    free(obj);
}

int main() {
    ProductOfNumbers* productOfNumbers = ProductOfNumbersCreate();
    add(productOfNumbers, 3);        // [3]
    add(productOfNumbers, 0);        // [3,0]
    add(productOfNumbers, 2);        // [3,0,2]
    add(productOfNumbers, 5);        // [3,0,2,5]
    add(productOfNumbers, 4);        // [3,0,2,5,4]
    printf("%d\n", getProduct(productOfNumbers, 2)); // return 20
    printf("%d\n", getProduct(productOfNumbers, 3)); // return 40
    printf("%d\n", getProduct(productOfNumbers, 4)); // return 0
    add(productOfNumbers, 8);        // [3,0,2,5,4,8]
    printf("%d\n", getProduct(productOfNumbers, 2)); // return 32
    ProductOfNumbersFree(productOfNumbers);
    return 0;
}