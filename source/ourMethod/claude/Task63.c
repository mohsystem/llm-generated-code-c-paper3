
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <jansson.h>

#define MAX_BUFFER_SIZE 4096
#define B64_DECODE_ERROR -1

typedef struct {
    char* data;
    size_t length;
} SafeString;

// Base64 decoding lookup table
static const unsigned char b64_table[256] = {
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,62,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,63,
    52,53,54,55,56,57,58,59,60,61,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
    15,16,17,18,19,20,21,22,23,24,25,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR,
    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,51,B64_DECODE_ERROR,B64_DECODE_ERROR,
    B64_DECODE_ERROR,B64_DECODE_ERROR,B64_DECODE_ERROR
};

SafeString* base64_decode(const char* input) {
    if (!input) return NULL;
    
    size_t input_len = strlen(input);
    if (input_len == 0 || input_len % 4 != 0) return NULL;

    // Allocate memory for decoded data
    size_t output_len = (input_len / 4) * 3;
    if (input[input_len - 1] == '=') output_len--;
    if (input[input_len - 2] == '=') output_len--;

    SafeString* result = (SafeString*)malloc(sizeof(SafeString));
    if (!result) return NULL;

    result->data = (char*)malloc(output_len + 1);
    if (!result->data) {
        free(result);
        return NULL;
    }
    result->length = output_len;

    // Decode
    size_t i, j = 0;
    uint32_t triple;

    for (i = 0; i < input_len; i += 4) {
        triple = 0;
        int k;
        for (k = 0; k < 4; k++) {
            unsigned char val = b64_table[(unsigned char)input[i + k]];
            if (val == B64_DECODE_ERROR) {
                free(result->data);
                free(result);
                return NULL;
            }
            triple = (triple << 6) | val;
        }

        if (j < output_len) result->data[j++] = (triple', type='text')