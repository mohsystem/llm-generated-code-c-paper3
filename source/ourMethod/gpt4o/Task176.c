#include <stdio.h>

typedef struct {
    int prefixProducts[40001];
    int size;
} ProductOfNumbers;

void ProductOfNumbersInit(ProductOfNumbers* obj) {
    obj->prefixProducts[0] = 1;
    obj->size = 1;
}

void ProductOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 1;
    } else {
        obj->prefixProducts[obj->size] = obj->prefixProducts[obj->size - 1] * num;
        obj->size++;
    }
}

int ProductOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    return obj->prefixProducts[obj->size - 1] / obj->prefixProducts[obj->size - k - 1];
}

int main() {
    ProductOfNumbers productOfNumbers;
    ProductOfNumbersInit(&productOfNumbers);
    ProductOfNumbersAdd(&productOfNumbers, 3);
    ProductOfNumbersAdd(&productOfNumbers, 0);
    ProductOfNumbersAdd(&productOfNumbers, 2);
    ProductOfNumbersAdd(&productOfNumbers, 5);
    ProductOfNumbersAdd(&productOfNumbers, 4);
    printf("%d\n", ProductOfNumbersGetProduct(&productOfNumbers, 2)); // 20
    printf("%d\n", ProductOfNumbersGetProduct(&productOfNumbers, 3)); // 40
    printf("%d\n", ProductOfNumbersGetProduct(&productOfNumbers, 4)); // 0
    ProductOfNumbersAdd(&productOfNumbers, 8);
    printf("%d\n", ProductOfNumbersGetProduct(&productOfNumbers, 2)); // 32
    return 0;
}