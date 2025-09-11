
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define KEY_SIZE 32  // 256 bits

char* generate_key() {
    unsigned char key[KEY_SIZE];
    char* hex_key = (char*)malloc(KEY_SIZE * 2 + 1);
    
    if (!hex_key) {
        return NULL;
    }
    
    if (RAND_bytes(key, KEY_SIZE) != 1) {
        free(hex_key);
        return NULL;
    }
    
    for(int i = 0; i < KEY_SIZE; i++) {
        sprintf(hex_key + (i * 2), "%02x", key[i]);
    }
    hex_key[KEY_SIZE * 2] = '\\0';
    
    return hex_key;
}

unsigned char* load_key(const char* hex_key, size_t* out_len) {
    size_t key_len = strlen(hex_key) / 2;
    unsigned char* key = (unsigned char*)malloc(key_len);
    
    if (!key) {
        return NULL;
    }
    
    for(size_t i = 0; i < key_len; i++) {
        sscanf(hex_key + (i * 2), "%2hhx", &key[i]);
    }
    
    *out_len = key_len;
    return key;
}

void free_key(void* key) {
    if (key) {
        memset(key, 0, KEY_SIZE);
        free(key);
    }
}

int main() {
    // Test Case 1: Generate new key
    char* key1 = generate_key();
    if (key1) {
        printf("Generated Key 1: %s\\n", key1);
    }
    
    // Test Case 2: Load generated key
    size_t key1_len;
    unsigned char* loaded_key1 = load_key(key1, &key1_len);
    if (loaded_key1) {
        printf("Loaded Key 1 Length: %zu\\n", key1_len);
    }
    
    // Test Case 3: Generate another key
    char* key2 = generate_key();
    if (key2) {
        printf("Generated Key 2: %s\\n", key2);
    }
    
    // Test Case 4: Verify keys are different
    if (key1 && key2) {
        printf("Keys are different: %d\\n", strcmp(key1, key2) != 0);
    }
    
    // Test Case 5: Verify key length
    if (loaded_key1) {
        printf("Key length (bits): %zu\\n", key1_len * 8);
    }
    
    // Cleanup
    free_key(key1);
    free_key(key2);
    free_key(loaded_key1);
    
    return 0;
}
