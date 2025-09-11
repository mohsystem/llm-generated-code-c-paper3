
// Task124.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define MAX_DATA_LEN 256

void encrypt_data(const char* data, unsigned char* encrypted) {
    unsigned char key[32];
    RAND_bytes(key, sizeof(key));
    
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 256, &aesKey);
    
    size_t len = strlen(data);
    size_t padded_len = ((len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    unsigned char* padded_data = (unsigned char*)calloc(padded_len, 1);
    memcpy(padded_data, data, len);
    
    for(size_t i = 0; i < padded_len; i += AES_BLOCK_SIZE) {
        AES_encrypt(padded_data + i, encrypted + i, &aesKey);
    }
    
    free(padded_data);
}

int main() {
    const char* test_data[] = {
        "4532-7153-3790-4421",
        "John Doe SSN: 123-45-6789",
        "Account#: 987654321",
        "Password: Secret123!",
        "Address: 123 Main St"
    };
    
    unsigned char encrypted[MAX_DATA_LEN];
    
    for(int i = 0; i < 5; i++) {
        printf("Original: %s\\n", test_data[i]);
        encrypt_data(test_data[i], encrypted);
        printf("Encrypted: ");
        for(size_t j = 0; j < strlen(test_data[i]); j++) {
            printf("%02x", encrypted[j]);
        }
        printf("\\n\\n");
    }
    
    return 0;
}
