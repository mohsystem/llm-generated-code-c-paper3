#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* deserialize(const char* data, const char* format) {
    void* result = malloc(100);
    if (strcmp(format, "string") == 0) {
        strcpy((char*)result, data);
    } else if (strcmp(format, "int") == 0) {
        *(int*)result = atoi(data);
    } else if (strcmp(format, "double") == 0) {
        *(double*)result = atof(data);
    }
    return result;
}

int main() {
    // Test case 1: Deserializing a string
    char* data1 = "Hello World";
    printf("%s\n", (char*)deserialize(data1, "string"));

    // Test case 2: Deserializing an integer
    char* data2 = "12345";
    printf("%d\n", *(int*)deserialize(data2, "int"));

    // Test case 3: Deserializing a double
    char* data3 = "3.14159";
    printf("%f\n", *(double*)deserialize(data3, "double"));

    // Test case 4: Deserializing a boolean
    char* data4 = "1"; // true
    printf("%d\n", *(int*)deserialize(data4, "int"));

    // Test case 5: Deserializing a custom format (not implemented)
    // No custom deserialization in C for complex objects in this example

    return 0;
}