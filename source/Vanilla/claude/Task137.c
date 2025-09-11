
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

struct Product {
    int id;
    char name[MAX_NAME_LENGTH];
    double price;
};

struct Product productTable[MAX_PRODUCTS];
int productCount = 0;

struct Product* getProductDetails(int productId) {
    for(int i = 0; i < productCount; i++) {
        if(productTable[i].id == productId) {
            return &productTable[i];
        }
    }
    return NULL;
}

void addProduct(int id, const char* name, double price) {
    if(productCount < MAX_PRODUCTS) {
        productTable[productCount].id = id;
        strncpy(productTable[productCount].name, name, MAX_NAME_LENGTH - 1);
        productTable[productCount].name[MAX_NAME_LENGTH - 1] = '\\0';
        productTable[productCount].price = price;
        productCount++;
    }
}

int main() {
    // Initialize product table with sample data
    addProduct(1, "Laptop", 999.99);
    addProduct(2, "Phone", 599.99);
    addProduct(3, "Tablet", 299.99);
    addProduct(4, "Watch", 199.99);
    addProduct(5, "Headphones", 99.99);
    
    // Test cases
    int testIds[] = {1, 2, 3, 4, 5};
    int testCount = 5;
    
    for(int i = 0; i < testCount; i++) {
        struct Product* product = getProductDetails(testIds[i]);
        if(product != NULL) {
            printf("Product ID: %d\\n", product->id);
            printf("Name: %s\\n", product->name);
            printf("Price: $%.2f\\n", product->price);
            printf("---------------\\n");
        }
    }
    
    return 0;
}
