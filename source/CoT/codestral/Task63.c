// This code snippet assumes that the JSON data is a simple key-value pair.
// For complex JSON structures, additional parsing logic will be required.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>
#include <jansson.h>

json_t* processRequest(const char* rawData) {
    int decodedLength = base64_decode_strlen(rawData);
    char* decodedData = malloc(decodedLength + 1);
    base64_decode(decodedData, rawData, decodedLength);
    decodedData[decodedLength] = '\0';

    json_error_t error;
    json_t* jsonData = json_loads(decodedData, 0, &error);

    free(decodedData);
    return jsonData;
}

int main() {
    // Test cases
    const char* testData1 = "eyJuYW1lIjoiSm9obiIsImVtYWlsIjoiSm9obi5Kb2huQGVtYWlsLmNvbSJ9";
    json_t* result = processRequest(testData1);
    printf("%s\n", json_dumps(result, 0));
    json_decref(result);
    // Add more test cases as needed
    return 0;
}