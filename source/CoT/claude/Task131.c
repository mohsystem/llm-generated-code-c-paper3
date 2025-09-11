
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_OUTPUT_LENGTH 768  // 3/4 of input length for Base64

// Structure to hold deserialized data
typedef struct {
    unsigned char* data;
    size_t length;
} DeserializedData;

// Function to check if string is valid Base64
int isBase64(const char* input) {
    if (!input) return 0;
    
    size_t len = strlen(input);
    if (len == 0) return 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isalnum(input[i]) && input[i] != '+' && input[i] != '/' && input[i] != '=') {
            return 0;
        }
    }
    
    // Check padding
    if (len % 4 != 0) return 0;
    
    return 1;
}

// Function to decode Base64
DeserializedData* deserializeData(const char* input) {
    if (!input) {
        fprintf(stderr, "Error: Input is NULL\\n");
        return NULL;
    }
    
    if (!isBase64(input)) {
        fprintf(stderr, "Error: Invalid Base64 format\\n");
        return NULL;
    }
    
    DeserializedData* result = (DeserializedData*)malloc(sizeof(DeserializedData));
    if (!result) {
        fprintf(stderr, "Error: Memory allocation failed\\n");
        return NULL;
    }
    
    size_t input_len = strlen(input);
    result->data = (unsigned char*)malloc(MAX_OUTPUT_LENGTH);
    if (!result->data) {
        free(result);
        fprintf(stderr, "Error: Memory allocation failed\\n");
        return NULL;
    }
    
    // Simple Base64 decoding implementation
    static const unsigned char decode_table[256] = {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
        64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
        64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
    };
    
    size_t output_len = 0;
    unsigned char* out = result->data;
    const unsigned char* in = (const unsigned char*)input;
    
    while (*in) {
        unsigned char a = decode_table[*in++];
        unsigned char b = decode_table[*in++];
        unsigned char c = decode_table[*in++];
        unsigned char d = decode_table[*in++];
        
        if (a == 64 || b == 64) break;
        
        *out++ = (a << 2) | (b >> 4);
        output_len++;
        
        if (c == 64) break;
        *out++ = (b << 4) | (c >> 2);
        output_len++;
        
        if (d == 64) break;
        *out++ = (c << 6) | d;
        output_len++;
    }
    
    result->length = output_len;
    result->data[output_len] = '\\0';
    
    return result;
}

void freeDeserializedData(DeserializedData* data) {
    if (data) {
        if (data->data) {
            free(data->data);
        }
        free(data);
    }
}

int main() {
    // Test cases
    const char* testCases[] = {
        "Sm9obg==",          // "John" in Base64
        "",                  // Empty string
        "invalid-base64!",   // Invalid Base64
        "SGVsbG8hISE=",     // "Hello!!!" in Base64
        "VGVzdA=="          // "Test" in Base64
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Test case %d: %s\\n", i + 1, testCases[i]);
        
        DeserializedData* result = deserializeData(testCases[i]);
        if (result) {
            printf("Success: %s\\n", result->data);
            freeDeserializedData(result);
        } else {
            printf("Error: Deserialization failed\\n");
        }
        printf("\\n");
    }
    
    return 0;
}
