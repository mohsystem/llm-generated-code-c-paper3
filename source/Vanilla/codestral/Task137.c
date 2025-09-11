#include <stdio.h>
#include <string.h>

char* productTable[][2] = {
    {"Apple", "A red fruit"},
    {"Banana", "A yellow fruit"},
    // Add more products as needed
};

char* getProductDetails(char* productName) {
    for (int i = 0; i < sizeof(productTable) / sizeof(productTable[0]); i++) {
        if (strcmp(productTable[i][0], productName) == 0) {
            return productTable[i][1];
        }
    }
    return "Product not found";
}

int main() {
    printf("%s\n", getProductDetails("Apple"));
    printf("%s\n", getProductDetails("Banana"));
    printf("%s\n", getProductDetails("Orange"));
    return 0;
}