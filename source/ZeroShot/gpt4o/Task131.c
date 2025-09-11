#include <stdio.h>
#include <string.h>

char* deserialize(const char* data) {
    if (data == NULL || strlen(data) == 0) {
        return "Deserialization failed: No data";
    }
    return (char*)data;
}

int main() {
    // Test cases
    printf("%s\n", deserialize("")); // Empty data
    printf("%s\n", deserialize("test")); // Random data
    printf("%s\n", deserialize("1234")); // Random numeric data
    printf("%s\n", deserialize("Hello")); // Text data
    printf("%s\n", deserialize("C")); // Text data
    return 0;
}