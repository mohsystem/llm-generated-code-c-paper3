#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h> // Include a base64 decoding library
#include <json/json.h> // Include jsoncpp library for JSON parsing (Note: jsoncpp is C++ and not directly usable in C, use a C JSON parser like jsmn)

void processRequest(const char* raw_data) {
    // Step 1: Ensure raw_data is encoded in UTF-8
    if (raw_data == NULL || *raw_data == '\0') {
        fprintf(stderr, "Raw data is empty or null\n");
        return;
    }

    // Step 2: Decode raw_data using Base64
    size_t decoded_len = base64_decoded_length(strlen(raw_data));
    char* decoded_data = (char*)malloc(decoded_len + 1);
    if (base64_decode(raw_data, strlen(raw_data), decoded_data, &decoded_len) != 0) {
        free(decoded_data);
        fprintf(stderr, "Failed to decode base64\n");
        return;
    }
    decoded_data[decoded_len] = '\0';

    // Step 3: Deserialize the decoded data into its original format
    // For simplicity, this example uses a basic JSON parsing approach.
    // In a real application, use a robust JSON parser like jsmn.
    if (strncmp(decoded_data, "{", 1) == 0) { // Simplified JSON check
        printf("%s\n", decoded_data); // Print JSON data
    } else if (strncmp(decoded_data, "<", 1) == 0 && strrchr(decoded_data, '>') != NULL) { // Simplified XML check
        printf("%s\n", decoded_data); // Print XML data
    } else {
        fprintf(stderr, "Failed to deserialize data\n");
    }

    free(decoded_data);
}

int main() {
    const char* testCases[] = {
        "SGVsbG8gd29ybGQh", // Base64 encoded "Hello world!"
        "eyJhbGdvcml0aG0iOiJzdWIiLCJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIjoiMjMwfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c", // Invalid JSON
        "<resource><resource></resource></resource>", // Valid XML
    };

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        processRequest(testCases[i]);
    }

    return 0;
}