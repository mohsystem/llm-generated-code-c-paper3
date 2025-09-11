// Note: This is a simplified version, it does not include JSON parsing as C does not have built-in JSON parsing.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

char* processRequest(const char* rawData) {
    size_t decodedLength = base64_decoded_length(rawData, strlen(rawData));
    char* decodedData = (char*)malloc(decodedLength + 1);
    base64_decode(rawData, strlen(rawData), decodedData);
    decodedData[decodedLength] = '\0';
    return decodedData;
}

int main() {
    const char* testData = "eyJrZXkiOiAidmFsdWUifQ=="; // Base64 encoded {"key": "value"}
    char* decodedData = processRequest(testData);
    printf("%s\n", decodedData);
    free(decodedData);
    return 0;
}