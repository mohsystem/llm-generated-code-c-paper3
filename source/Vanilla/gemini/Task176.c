#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *prefixProducts;
    int size;
    int capacity;
} ProductOfNumbers;

void init(ProductOfNumbers *obj) {
    obj->capacity = 10; // Initial capacity
    obj->prefixProducts = (int *)malloc(obj->capacity * sizeof(int));
    obj->size = 0;
    if (obj->prefixProducts == NULL) {
        perror("Failed to allocate memory");
        exit(1); // Exit with error code if allocation fails
    }
    obj->prefixProducts[obj->size++] = 1;
}

void add(ProductOfNumbers *obj, int num) {
    if (num == 0) {
        obj->size = 0;
        obj->prefixProducts[obj->size++] = 1;
    } else {
        if (obj->size == obj->capacity) {
            obj->capacity *= 2;
            obj->prefixProducts = (int *)realloc(obj->prefixProducts, obj->capacity * sizeof(int));
            if (obj->prefixProducts == NULL) {
                 perror("Failed to reallocate memory");
                 exit(1);
            }
        }
        obj->prefixProducts[obj->size++] = obj->prefixProducts[obj->size - 1] * num;
    }
}

int getProduct(ProductOfNumbers *obj, int k) {
    if (k >= obj->size) {
        return 0;
    }
    return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - 1 - k];
}

void freeMemory(ProductOfNumbers *obj) {
    free(obj->prefixProducts);
}

int main() {
    ProductOfNumbers productOfNumbers;
    init(&productOfNumbers);
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
    init(&productOfNumbers2);
    add(&productOfNumbers2, 1);
    printf("%d\n", getProduct(&productOfNumbers2, 1)); // 1


    ProductOfNumbers productOfNumbers3;
    init(&productOfNumbers3);
    add(&productOfNumbers3, 10);
    add(&productOfNumbers3, 5);
    add(&productOfNumbers3, 2);
    printf("%d\n", getProduct(&productOfNumbers3, 3)); // 100


    freeMemory(&productOfNumbers);
    freeMemory(&productOfNumbers2);
    freeMemory(&productOfNumbers3);
    return 0;
}