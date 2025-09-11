// C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double price;
} Product;

// Predefined product table
Product products[] = {
    {1, "Product1", 10.0},
    {2, "Product2", 20.0},
    // Add more products as needed
};

const int product_count = sizeof(products) / sizeof(products[0]);

const char* getProductDetails(int productId) {
    // Search for the product in the product table
    for (int i = 0; i < product_count; i++) {
        if (products[i].id == productId) {
            static char buffer[100];
            snprintf(buffer, sizeof(buffer), "Product ID: %d, Name: %s, Price: %.2f", products[i].id, products[i].name, products[i].price);
            return buffer;
        }
    }

    return "Product not found";
}

int main() {
    // Test cases
    printf("%s\n", getProductDetails(1));
    printf("%s\n", getProductDetails(3));
    return 0;
}