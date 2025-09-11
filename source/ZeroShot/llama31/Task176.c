#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefix;
    int size;
    int idx;
} ProductOfNumbers;

ProductOfNumbers* ProductOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*) malloc(sizeof(ProductOfNumbers));
    obj->prefix = (int*) malloc(sizeof(int) * 40001);
    obj->prefix[0] = 1;
    obj->size = 40001;
    obj->idx = 0;
    return obj;
}

void ProductOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->idx = 0;
        obj->prefix[0] = 1;
    } else {
        obj->idx++;
        if (obj->idx >= obj->size) {
            // Handle overflow, though it should not occur given the constraints
            obj->size *= 2;
            obj->prefix = realloc(obj->prefix, sizeof(int) * obj->size);
        }
        obj->prefix[obj->idx] = obj->prefix[obj->idx - 1] * num;
    }
}

int ProductOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    if (obj->idx < k) return 0;
    if (obj->prefix[obj->idx - k + 1] == 0) return 0;
    return obj->prefix[obj->idx] / obj->prefix[obj->idx - k + 1];
}

void ProductOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->prefix);
    free(obj);
}

int main() {
    ProductOfNumbers* productOfNumbers = ProductOfNumbersCreate();
    ProductOfNumbersAdd(productOfNumbers, 3);
    ProductOfNumbersAdd(productOfNumbers, 0);
    ProductOfNumbersAdd(productOfNumbers, 2);
    ProductOfNumbersAdd(productOfNumbers, 5);
    ProductOfNumbersAdd(productOfNumbers, 4);
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 2)); // Output: 20
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 3)); // Output: 40
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 4)); // Output: 0
    ProductOfNumbersAdd(productOfNumbers, 8);
    printf("%d\n", ProductOfNumbersGetProduct(productOfNumbers, 2)); // Output: 32
    ProductOfNumbersFree(productOfNumbers);
    return 0;
}