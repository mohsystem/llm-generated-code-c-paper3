#include <stdio.h>
#include <string.h>

// Define a simple structure to represent product details
struct Product {
    char name[50];
    char details[200];
};

// Function to search for a product and return its details
char* getProductDetails(char productName[], struct Product productTable[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        if (strcmp(productName, productTable[i].name) == 0) {
            return productTable[i].details;
        }
    }
    return "Product not found";
}

int main() {
    // Initialize the product table
    struct Product productTable[] = {
        {"Laptop", "Price: $1200, RAM: 16GB, Storage: 1TB SSD"},
        {"Mouse", "Price: $25, Wireless, Optical"},
        {"Keyboard", "Price: $75, Mechanical, RGB"},
        {"Monitor", "Price: $300, 27-inch, 144Hz"},
        {"Webcam", "Price: $50, 1080p, Built-in microphone"}
    };
    int tableSize = sizeof(productTable) / sizeof(productTable[0]);

    char testCases[][20] = {"Laptop", "Mouse", "Keyboard", "Monitor", "Webcam", "Nonexistent"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        printf("%s\n", getProductDetails(testCases[i], productTable, tableSize));
    }

    return 0;
}