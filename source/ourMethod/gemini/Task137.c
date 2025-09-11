#include <stdio.h>
#include <string.h>

// Define a simple struct for product details
struct Product {
    char name[50];
    char details[100];
};

// Function to search for product details
char* getProductDetails(const char* productName, struct Product productTable[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        if (strcmp(productName, productTable[i].name) == 0) {
            return productTable[i].details;
        }
    }
    return "Product not found.";
}

int main() {
    // Sample product table
    struct Product productTable[] = {
        {"Laptop", "Model: XPS 13, Price: $1200"},
        {"Mouse", "Model: MX Master 3, Price: $100"},
        {"Keyboard", "Model: G915, Price: $250"},
        {"Monitor", "Model: U2720Q, Price: $700"},
        {"Webcam", "Model: C920, Price: $60"}
    };
    int tableSize = sizeof(productTable) / sizeof(productTable[0]);

    // Test cases
    char* testCases[] = {"Laptop", "Mouse", "Keyboard", "Monitor", "NonExistent"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char* details = getProductDetails(testCases[i], productTable, tableSize);
        printf("%s\n", details);
    }

    return 0;
}