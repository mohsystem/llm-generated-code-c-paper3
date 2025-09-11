#include <stdio.h>
#include <string.h>

typedef struct {
    char code[4];
    char description[50];
} Product;

Product productTable[] = {
    {"001", "Product 1: Widget A"},
    {"002", "Product 2: Widget B"},
    {"003", "Product 3: Widget C"},
    {"004", "Product 4: Widget D"},
    {"005", "Product 5: Widget E"}
};

const char* getProductDetails(const char* productCode) {
    for (int i = 0; i < sizeof(productTable) / sizeof(Product); i++) {
        if (strcmp(productTable[i].code, productCode) == 0) {
            return productTable[i].description;
        }
    }
    return "Product not found";
}

int main() {
    printf("%s\n", getProductDetails("001")); // Test case 1
    printf("%s\n", getProductDetails("002")); // Test case 2
    printf("%s\n", getProductDetails("003")); // Test case 3
    printf("%s\n", getProductDetails("006")); // Test case 4
    printf("%s\n", getProductDetails("005")); // Test case 5
    return 0;
}