
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    double price;
} Product;

typedef struct {
    Product products[MAX_PRODUCTS];
    int count;
} ProductTable;

void initializeProducts(ProductTable* table) {
    table->count = 5;
    
    Product p1 = {1, "Laptop", 999.99};
    Product p2 = {2, "Phone", 599.99};
    Product p3 = {3, "Tablet", 299.99};
    Product p4 = {4, "Watch", 199.99};
    Product p5 = {5, "Headphones", 99.99};
    
    table->products[0] = p1;
    table->products[1] = p2;
    table->products[2] = p3;
    table->products[3] = p4;
    table->products[4] = p5;
}

int getProductDetails(ProductTable* table, int productId, Product* result) {
    if(productId <= 0) {
        return -1;  // Invalid ID
    }
    
    for(int i = 0; i < table->count; i++) {
        if(table->products[i].id == productId) {
            *result = table->products[i];
            return 0;  // Success
        }
    }
    
    return -2;  // Product not found
}

void printProduct(const Product* product) {
    printf("Product ID: %d, Name: %s, Price: $%.2f\\n", 
           product->id, product->name, product->price);
}

int main() {
    ProductTable table;
    Product result;
    initializeProducts(&table);
    
    // Test cases
    int testCases[] = {1, 3, -1, 10, 0};
    int numTests = 5;
    
    for(int i = 0; i < numTests; i++) {
        int status = getProductDetails(&table, testCases[i], &result);
        
        if(status == 0) {
            printProduct(&result);
        } else if(status == -1) {
            printf("Error: Invalid product ID\\n");
        } else {
            printf("Error: Product not found\\n");
        }
    }
    
    return 0;
}
