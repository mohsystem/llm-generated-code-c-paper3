
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define MAX_DATA_LEN 1024
#define KEY_LENGTH 256

typedef struct {
    unsigned char key[32]; // 256 bits
    AES_KEY enc_key;
    AES_KEY dec_key;
} Task124;

void init_secure_storage(Task124* storage) {
    if (RAND_bytes(storage->key, sizeof(storage->key)) != 1) {
        fprintf(stderr, "Error generating key\\n");
        exit(1);
    }
    
    if (AES_set_encrypt_key(storage->key, KEY_LENGTH, &storage->enc_key) < 0) {
        fprintf(stderr, "Error setting encryption key\\n");
        exit(1);
    }
    
    if (AES_set_decrypt_key(storage->key, KEY_LENGTH, &storage->dec_key) < 0) {
        fprintf(stderr, "Error setting decryption key\\n");
        exit(1);
    }
}

void encrypt_data(Task124* storage, const unsigned char* input, int input_len, 
                 unsigned char* output, int* output_len) {
    int padded_len = ((input_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_input = (unsigned char*)calloc(padded_len, 1);
    
    memcpy(padded_input, input, input_len);
    
    for (int i = 0; i < padded_len; i += AES_BLOCK_SIZE) {
        AES_encrypt(padded_input + i, output + i, &storage->enc_key);
    }
    
    *output_len = padded_len;
    free(padded_input);
}

void decrypt_data(Task124* storage, const unsigned char* input, int input_len,
                 unsigned char* output, int* output_len) {
    for (int i = 0; i < input_len; i += AES_BLOCK_SIZE) {
        AES_decrypt(input + i, output + i, &storage->dec_key);
    }
    
    // Remove padding
    *output_len = input_len;
    while (*output_len > 0 && output[*output_len - 1] == 0) {
        (*output_len)--;
    }
}

int main() {
    Task124 storage;
    init_secure_storage(&storage);
    
    // Test cases
    const char* test_data[] = {
        "4532-7153-3790-4421",
        "John Doe,123-45-6789",
        "jane.doe@email.com",
        "1234-5678-9012-3456",
        "987-65-4321,Alice Smith"
    };
    
    unsigned char encrypted[MAX_DATA_LEN];
    unsigned char decrypted[MAX_DATA_LEN];
    int encrypted_len, decrypted_len;
    
    for (int i = 0; i < 5; i++) {
        printf("Original: %s\\n", test_data[i]);
        
        encrypt_data(&storage, (unsigned char*)test_data[i], strlen(test_data[i]),
                    encrypted, &encrypted_len);
        
        printf("Encrypted: ");
        for (int j = 0; j < encrypted_len; j++) {
            printf("%02x", encrypted[j]);
        }
        printf("\\n");
        
        decrypt_data(&storage, encrypted, encrypted_len, decrypted, &decrypted_len);
        decrypted[decrypted_len] = '\\0';
        printf("Decrypted: %s\\n\\n", decrypted);
    }
    
    return 0;
}
