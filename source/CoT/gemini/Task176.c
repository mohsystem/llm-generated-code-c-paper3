#include <stdio.h>
#include <stdlib.h>

// Implement a dynamic array (since C doesn't have built-in dynamic arrays like C++ vectors)
typedef struct {
    int *arr;
    int size;
    int capacity;
} DynArray;

void initDynArray(DynArray *da) {
    da->arr = NULL;
    da->size = 0;
    da->capacity = 0;
}

void addDynArray(DynArray *da, int num) {
    if (da->size == da->capacity) {
        da->capacity = (da->capacity == 0) ? 1 : da->capacity * 2;
        da->arr = realloc(da->arr, da->capacity * sizeof(int));
    }
    da->arr[da->size++] = num;
}

void clearDynArray(DynArray *da) {
    da->size = 0;
}

typedef struct {
    DynArray prefixProducts;
} ProductOfNumbers;

void initProductOfNumbers(ProductOfNumbers *pon) {
    initDynArray(&pon->prefixProducts);
    addDynArray(&pon->prefixProducts, 1);
}

void add(ProductOfNumbers *pon, int num) {
    if (num == 0) {
        clearDynArray(&pon->prefixProducts);
        addDynArray(&pon->prefixProducts, 1);
    } else {
        int lastProduct = pon->prefixProducts.arr[pon->prefixProducts.size - 1];
        addDynArray(&pon->prefixProducts, lastProduct * num);
    }
}

int getProduct(ProductOfNumbers *pon, int k) {
    int n = pon->prefixProducts.size;
    if (k >= n) {
        return 0;
    }
    return pon->prefixProducts.arr[n - 1] / pon->prefixProducts.arr[n - 1 - k];
}


int main() {
    ProductOfNumbers productOfNumbers;
    initProductOfNumbers(&productOfNumbers);

    add(&productOfNumbers, 3);
    add(&productOfNumbers, 0);
    add(&productOfNumbers, 2);
    add(&productOfNumbers, 5);
    add(&productOfNumbers, 4);
    printf("%d\n", getProduct(&productOfNumbers, 2)); // 20
    printf("%d\n", getProduct(&productOfNumbers, 3)); // 40
    printf("%d\n", getProduct(&productOfNumbers, 4)); // 0
    add(&productOfNumbers, 8);
    printf("%d\n", getProduct(&productOfNumbers, 2)); // 32

        ProductOfNumbers productOfNumbers2;
    initProductOfNumbers(&productOfNumbers2);

    add(&productOfNumbers2, 1);
    add(&productOfNumbers2, 2);
    add(&productOfNumbers2, 3);
    add(&productOfNumbers2, 4);
    add(&productOfNumbers2, 5);
    printf("%d\n", getProduct(&productOfNumbers2, 2)); // 20
    printf("%d\n", getProduct(&productOfNumbers2, 3)); // 60
    printf("%d\n", getProduct(&productOfNumbers2, 4)); // 120
    add(&productOfNumbers2, 0);
    add(&productOfNumbers2, 2);
    add(&productOfNumbers2, 2);
    printf("%d\n", getProduct(&productOfNumbers2, 2)); // 4
    printf("%d\n", getProduct(&productOfNumbers2, 3)); // 8
    printf("%d\n", getProduct(&productOfNumbers2, 4)); // 0
    return 0;
}