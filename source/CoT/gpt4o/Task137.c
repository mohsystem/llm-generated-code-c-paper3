#include <stdio.h>
#include <string.h>

typedef struct {
    const char* name;
    double price;
} Product;

Product productTable[] = {
    {"P001", "Laptop", 1500.0},
    {"P002", "Smartphone", 800.0},
    {"P003", "Headphones", 150.0},
    {"P004", "Monitor", 300.0},
    {"P005", "Keyboard", 100.0}
};

const int productCount = sizeof(productTable) / sizeof(productTable[0]);

Product* inquireProduct(const char* productId) {
    for (int i = 0; i < productCount; ++i) {
        if (strcmp(productTable[i].name, productId) == 0) {
            return &productTable[i];
        }
    }
    return NULL;
}

int main() {
    const char* testCases[] = {"P001", "P002", "P003", "P006", "P005"};
    for (int i = 0; i < 5; ++i) {
        Product* product = inquireProduct(testCases[i]);
        if (product) {
            printf("Found: Product{name='%s', price=%.2f}\n", product->name, product->price);
        } else {
            printf("Product ID %s not found.\n", testCases[i]);
        }
    }
    return 0;
}