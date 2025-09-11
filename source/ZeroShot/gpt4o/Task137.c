#include <stdio.h>
#include <string.h>

const char* getProductDetails(int productId) {
    static struct { int id; const char *details; } productTable[] = {
        {1, "Product 1 details"},
        {2, "Product 2 details"},
        {3, "Product 3 details"},
        {4, "Product 4 details"},
        {5, "Product 5 details"}
    };
    int tableSize = sizeof(productTable) / sizeof(productTable[0]);
    for (int i = 0; i < tableSize; i++) {
        if (productTable[i].id == productId) {
            return productTable[i].details;
        }
    }
    return "Product not found";
}

int main() {
    printf("%s\n", getProductDetails(1)); // Expected: Product 1 details
    printf("%s\n", getProductDetails(3)); // Expected: Product 3 details
    printf("%s\n", getProductDetails(5)); // Expected: Product 5 details
    printf("%s\n", getProductDetails(7)); // Expected: Product not found
    printf("%s\n", getProductDetails(2)); // Expected: Product 2 details
    return 0;
}