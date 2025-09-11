#include <stdio.h>
#include <string.h>

// Sample product table
typedef struct {
    char name[50];
    char details[100];
} Product;

Product productTable[] = {
    {"Product1", "Details of Product1"},
    {"Product2", "Details of Product2"},
    {"Product3", "Details of Product3"},
    {"", ""} // Terminator
};

char* getProductDetails(const char* productName) {
    if (productName == NULL || *productName == '\0') {
        return "Product name cannot be empty.";
    }

    for (int i = 0; productTable[i].name[0] != '\0'; ++i) {
        if (strcmp(productTable[i].name, productName) == 0) {
            return productTable[i].details;
        }
    }

    return "Product not found.";
}

int main() {
    const char* testCases[] = {"Product1", "Product2", "Product3", "InvalidProduct", ""};

    for (int i = 0; i < 5; ++i) {
        printf("Enter product name: %s\n", testCases[i]);
        char* productDetails = getProductDetails(testCases[i]);
        printf("Product Details: %s\n", productDetails);
        printf("----------------------------\n");
    }

    return 0;
}