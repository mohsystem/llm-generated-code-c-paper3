#include <stdio.h>
#include <string.h>

typedef struct {
    char id[10];
    char name[50];
    double price;
} Product;

Product* getProductDetails(Product* products, int size, const char* productId) {
    // Secure coding practice: Avoid null pointer exceptions
    if (products == NULL || size <= 0 || productId == NULL) {
        return NULL;
    }

    // Iterate through the product table
    for (int i = 0; i < size; i++) {
        if (strcmp(products[i].id, productId) == 0) {
            return &products[i];
        }
    }

    return NULL;
}

int main() {
    // Sample product table
    Product products[] = {
        {"1", "Product A", 10.99},
        {"2", "Product B", 9.99},
        {"3", "Product C", 12.99}
    };

    int size = sizeof(products) / sizeof(products[0]);

    // Test cases
    const char* testCases[] = {"1", "2", "3", "4", "invalid"};

    for (int i = 0; i < 5; i++) {
        Product* product = getProductDetails(products, size, testCases[i]);
        if (product != NULL) {
            printf("Product ID: %s\n", product->id);
            printf("Product Name: %s\n", product->name);
            printf("Product Price: $%.2f\n", product->price);
        } else {
            printf("Product not found.\n");
        }
    }

    return 0;
}