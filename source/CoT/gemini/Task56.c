#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simplified base64 encoding (not fully compliant) for demonstration
char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length) {
    *output_length = 4 * ((input_length + 2) / 3);
    char* encoded_data = (char*)malloc(*output_length + 1);
    if (encoded_data == NULL) return NULL;

    // ... (Base64 encoding logic would go here) ...
    // Note: Using a proper Base64 library is highly recommended in production.

    return encoded_data;
}

char* generateToken() {
    unsigned char randomBytes[24];
    srand(time(NULL)); // Initialize random seed

    for (int i = 0; i < 24; i++) {
        randomBytes[i] = rand() % 256;
    }

    size_t encodedLength;
    char* encodedToken = base64_encode(randomBytes, 24, &encodedLength);
    //In a real application, error handling for base64_encode should be added

    return encodedToken;
}


int main() {
    for (int i = 0; i < 5; i++) {
        char* token = generateToken();
        if (token) {
            printf("%s\n", token);
            free(token);
        }
    }
    return 0;
}