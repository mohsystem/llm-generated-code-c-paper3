#include <stdio.h>
#include <string.h>

void storeSensitiveData(const char* data[], int size) {
    // Simulating secure storage (in real scenarios, use a secure database or encryption)
    for (int i = 0; i < size; i++) {
        printf("Storing: %s\n", data[i]);
        // Here you would typically use a secure method to store the data
        // For example, encrypting the data before storing it.
    }
}

int main() {
    // Test cases
    const char* dataToStore[] = {"1234-5678-9012-3456", "John Doe", "123 Main St"};
    int size = sizeof(dataToStore) / sizeof(dataToStore[0]);
    storeSensitiveData(dataToStore, size);
    return 0;
}