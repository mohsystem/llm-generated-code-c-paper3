
typedef struct {
    int prefix[40000];
    int size;
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    obj->size = 1;
    obj->prefix[0] = 1;
    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 1;
        obj->prefix[0] = 1;
    } else {
        obj->prefix[obj->size] = obj->prefix[obj->size - 1] * num;
        obj->size++;
    }
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    if (k >= obj->size) return 0;
    return obj->prefix[obj->size - 1] / obj->prefix[obj->size - k - 1];
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj);
}

int main() {
    // Test case 1
    ProductOfNumbers* pn = productOfNumbersCreate();
    productOfNumbersAdd(pn, 3);
    productOfNumbersAdd(pn, 0);
    productOfNumbersAdd(pn, 2);
    productOfNumbersAdd(pn, 5);
    productOfNumbersAdd(pn, 4);
    printf("%d\\n", productOfNumbersGetProduct(pn, 2)); // 20
    productOfNumbersFree(pn);
    
    // Test case 2
    ProductOfNumbers* pn2 = productOfNumbersCreate();
    productOfNumbersAdd(pn2, 2);
    productOfNumbersAdd(pn2, 3);
    productOfNumbersAdd(pn2, 4);
    printf("%d\\n", productOfNumbersGetProduct(pn2, 3)); // 24
    productOfNumbersFree(pn2);
    
    // Test case 3
    ProductOfNumbers* pn3 = productOfNumbersCreate();
    productOfNumbersAdd(pn3, 1);
    productOfNumbersAdd(pn3, 1);
    productOfNumbersAdd(pn3, 1);
    printf("%d\\n", productOfNumbersGetProduct(pn3, 2)); // 1
    productOfNumbersFree(pn3);
    
    // Test case 4
    ProductOfNumbers* pn4 = productOfNumbersCreate();
    productOfNumbersAdd(pn4, 5);
    productOfNumbersAdd(pn4, 0);
    productOfNumbersAdd(pn4, 2);
    printf("%d\\n", productOfNumbersGetProduct(pn4, 2)); // 0
    productOfNumbersFree(pn4);
    
    // Test case 5
    ProductOfNumbers* pn5 = productOfNumbersCreate();
    productOfNumbersAdd(pn5, 2);
    productOfNumbersAdd(pn5, 5);
    productOfNumbersAdd(pn5, 3);
    productOfNumbersAdd(pn5, 4);
    printf("%d\\n", productOfNumbersGetProduct(pn5, 4)); // 120
    productOfNumbersFree(pn5);
    
    return 0;
}
