
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define TOKEN_LENGTH_BYTES 32

// Base64 encoding table
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

char* generate_token() {
    unsigned char* random_bytes = (unsigned char*)malloc(TOKEN_LENGTH_BYTES);
    if (!random_bytes) {
        return NULL;
    }
    
    // Use /dev/urandom for secure random generation on Unix systems
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (!urandom) {
        free(random_bytes);
        return NULL;
    }
    
    size_t bytes_read = fread(random_bytes, 1, TOKEN_LENGTH_BYTES, urandom);
    fclose(urandom);
    
    if (bytes_read != TOKEN_LENGTH_BYTES) {
        free(random_bytes);
        return NULL;
    }
    
    // Get timestamp
    time_t timestamp = time(NULL);
    char ts_str[21];
    snprintf(ts_str, sizeof(ts_str), "%ld", timestamp);
    size_t ts_len = strlen(ts_str);
    
    // Combine random bytes and timestamp
    size_t total_len = TOKEN_LENGTH_BYTES + ts_len;
    unsigned char* token_bytes = (unsigned char*)malloc(total_len);
    if (!token_bytes) {
        free(random_bytes);
        return NULL;
    }
    
    memcpy(token_bytes, random_bytes, TOKEN_LENGTH_BYTES);
    memcpy(token_bytes + TOKEN_LENGTH_BYTES, ts_str, ts_len);
    free(random_bytes);
    
    // Base64 encode
    size_t encoded_len = ((total_len + 2) / 3) * 4 + 1;
    char* encoded = (char*)malloc(encoded_len);
    if (!encoded) {
        free(token_bytes);
        return NULL;
    }
    
    size_t i, j = 0;
    for(i = 0; i < total_len; i += 3) {
        uint32_t octet_a = i < total_len ? token_bytes[i] : 0;
        uint32_t octet_b = i + 1 < total_len ? token_bytes[i + 1] : 0;
        uint32_t octet_c = i + 2 < total_len ? token_bytes[i + 2] : 0;
        
        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        
        encoded[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded[j++] = base64_table[triple & 0x3F];
    }
    
    free(token_bytes);
    encoded[j] = '\\0';
    
    return encoded;
}

int main() {
    // Test token generation 5 times
    for(int i = 0; i < 5; i++) {
        char* token = generate_token();
        if (token) {
            printf("Generated Token %d: %s\\n", i+1, token);
            free(token);
        } else {
            printf("Failed to generate token %d\\n", i+1);
        }
    }
    
    return 0;
}
