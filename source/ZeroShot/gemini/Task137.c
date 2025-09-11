#include <stdio.h>
#include <string.h>

struct Product {
    char name[50];
    double price;
};


// Simulate a product table (replace with your actual storage mechanism)
struct Product productTable[3] = {
    {"Product A", 10.99},
    {"Product B", 25.50},
    {"Product C", 5.75}
};
char productIds[3][10] = {"A123", "B456", "C789"};


struct Product* getProductDetails(const char* productId) {

    for (int i = 0; i < 3; i++) {
        if (strcmp(productId, productIds[i]) == 0) {
            return &productTable[i];
        }
    }
    return NULL;
}

int main() {
    // Test Cases
    printf("%s\n", (getProductDetails("A123") ? "Found" : "Not Found"));
    printf("%s\n", (getProductDetails("B456") ? "Found" : "Not Found"));
    printf("%s\n", (getProductDetails("C789") ? "Found" : "Not Found"));
    printf("%s\n", (getProductDetails("InvalidID") ? "Found" : "Not Found"));
    printf("%s\n", (getProductDetails("") ? "Found" : "Not Found"));

    return 0;
}