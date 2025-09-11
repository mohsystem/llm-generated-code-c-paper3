#include <stdio.h>
#include <string.h>

// Mock product table
typedef struct Product {
    char id[10];
    char name[50];
    char price[10];
} Product;

Product productTable[] = {
    {"1", "Product A", "10.99"},
    {"2", "Product B", "9.99"},
    {"3", "Product C", "12.99"},
    {"4", "Product D", "8.99"},
    {"5", "Product E", "11.99"}
};

const int productCount = sizeof(productTable) / sizeof(Product);

char* getProductDetails(const char* productId) {
    static char result[100];
    for (int i = 0; i < productCount; i++) {
        if (strcmp(productTable[i].id, productId) == 0) {
            sprintf(result, "Product ID: %s, Name: %s, Price: %s", productTable[i].id, productTable[i].name, productTable[i].price);
            return result;
        }
    }
    strcpy(result, "Product not found");
    return result;
}

int main() {
    // Test cases
    printf("%s\n", getProductDetails("1"));
    printf("%s\n", getProductDetails("2"));
    printf("%s\n", getProductDetails("3"));
    printf("%s\n", getProductDetails("4"));
    printf("%s\n", getProductDetails("5"));

    return 0;
}