#include <stdio.h>
#include <string.h>

const char* deserialize(const char* data) {
    if (data == NULL || strlen(data) == 0) return "";
    return data;
}

int main() {
    // Test cases
    const char* testData1 = "";  // Empty input
    const char* testData2 = NULL;  // Null input
    const char* testData3 = " ";  // Minimal data input
    const char* testData4 = "invalid";  // Invalid serialized data
    const char* testData5 = "invalid";  // Invalid serialized data

    printf("%s\n", deserialize(testData1));
    printf("%s\n", deserialize(testData2));
    printf("%s\n", deserialize(testData3));
    printf("%s\n", deserialize(testData4));
    printf("%s\n", deserialize(testData5));

    return 0;
}