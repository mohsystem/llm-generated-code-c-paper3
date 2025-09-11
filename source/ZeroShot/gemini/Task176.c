#include <stdio.h>
#include <stdlib.h>

// Implementing dynamic array functionalities since C doesn't have built-in dynamic arrays
typedef struct {
    int *arr;
    int size;
    int capacity;
} DynArr;

DynArr* createDynArr() {
    DynArr *dynArr = (DynArr*)malloc(sizeof(DynArr));
    dynArr->arr = (int*)malloc(sizeof(int) * 2);
    dynArr->size = 0;
    dynArr->capacity = 2;
    return dynArr;
}

void add(DynArr *dynArr, int num) {
    if (dynArr->size == dynArr->capacity) {
        dynArr->capacity *= 2;
        dynArr->arr = (int*)realloc(dynArr->arr, sizeof(int) * dynArr->capacity);
    }
    dynArr->arr[dynArr->size++] = num;
}

void clear(DynArr *dynArr) {
    dynArr->size = 0;
}

int get(DynArr *dynArr, int index) {
    return dynArr->arr[index];
}


typedef struct {
    DynArr *list;
} ProductOfNumbers;

ProductOfNumbers* createProductOfNumbers() {
    ProductOfNumbers *p = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    p->list = createDynArr();
    add(p->list, 1);
    return p;
}


void addProduct(ProductOfNumbers *p, int num) {
    if (num == 0) {
        clear(p->list);
        add(p->list, 1);
    } else {
        add(p->list, get(p->list, p->list->size - 1) * num);
    }
}

int getProduct(ProductOfNumbers *p, int k) {
    int n = p->list->size;
    if (k >= n) {
        return 0;
    }
    return get(p->list, n - 1) / get(p->list, n - 1 - k);
}

int main() {
    ProductOfNumbers *productOfNumbers = createProductOfNumbers();
    addProduct(productOfNumbers, 3);        // [3]
    addProduct(productOfNumbers, 0);        // [3,0]
    addProduct(productOfNumbers, 2);        // [3,0,2]
    addProduct(productOfNumbers, 5);        // [3,0,2,5]
    addProduct(productOfNumbers, 4);        // [3,0,2,5,4]
    printf("%d\n", getProduct(productOfNumbers, 2)); // return 20. The product of the last 2 numbers is 5 * 4 = 20
    printf("%d\n", getProduct(productOfNumbers, 3)); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
    printf("%d\n", getProduct(productOfNumbers, 4)); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
    addProduct(productOfNumbers, 8);        // [3,0,2,5,4,8]
    printf("%d\n", getProduct(productOfNumbers, 2)); // return 32. The product of the last 2 numbers is 4 * 8 = 32
    return 0;
}