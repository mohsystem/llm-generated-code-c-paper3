
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define AES_BLOCK_SIZE 16
#define MAX_DATA_LEN 256

typedef struct {
    unsigned char key[32];
    unsigned char iv[16];
    AES_KEY enc_key;
    AES_KEY dec_key;
} Task124;

void init_encryptor(Task124* encryptor) {
    // In production, use secure key generation and management
    const char* key_str = "MySuperSecretKey12345678901234567";
    const char* iv_str = "1234567890123456";
    
    memcpy(encryptor->key, key_str, 32);
    memcpy(encryptor->iv, iv_str, 16);
    
    AES_set_encrypt_key(encryptor->key, 256, &encryptor->enc_key);
    AES_set_decrypt_key(encryptor->key, 256, &encryptor->dec_key);
}

void encrypt(Task124* encryptor, unsigned char* plaintext, unsigned char* ciphertext, int length) {
    unsigned char iv[16];
    memcpy(iv, encryptor->iv, 16);
    
    // Ensure padding to block size
    int padded_len = ((length + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char padded_data[MAX_DATA_LEN];
    memcpy(padded_data, plaintext, length);
    memset(padded_data + length, 0, padded_len - length);
    
    AES_cbc_encrypt(padded_data, ciphertext, padded_len, &encryptor->enc_key, iv, AES_ENCRYPT);
}

void decrypt(Task124* encryptor, unsigned char* ciphertext, unsigned char* plaintext, int length) {
    unsigned char iv[16];
    memcpy(iv, encryptor->iv, 16);
    
    AES_cbc_encrypt(ciphertext, plaintext, length, &encryptor->dec_key, iv, AES_DECRYPT);
}

int main() {
    Task124 encryptor;
    init_encryptor(&encryptor);
    
    unsigned char ciphertext[MAX_DATA_LEN];
    unsigned char decrypted[MAX_DATA_LEN];
    
    // Test case 1
    const char* data1 = "4532-7153-3790-4421";
    encrypt(&encryptor, (unsigned char*)data1, ciphertext, strlen(data1));
    decrypt(&encryptor, ciphertext, decrypted, ((strlen(data1) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    printf("Test 1: Original: %s, Decrypted: %s\\n", data1, decrypted);
    
    // Test case 2
    const char* data2 = "SSN: 123-45-6789";
    encrypt(&encryptor, (unsigned char*)data2, ciphertext, strlen(data2));
    decrypt(&encryptor, ciphertext, decrypted, ((strlen(data2) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    printf("Test 2: Original: %s, Decrypted: %s\\n", data2, decrypted);
    
    // Test case 3
    const char* data3 = "Password123!@#";
    encrypt(&encryptor, (unsigned char*)data3, ciphertext, strlen(data3));
    decrypt(&encryptor, ciphertext, decrypted, ((strlen(data3) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    printf("Test 3: Original: %s, Decrypted: %s\\n", data3, decrypted);
    
    // Test case 4
    const char* data4 = "user@email.com";
    encrypt(&encryptor, (unsigned char*)data4, ciphertext, strlen(data4));
    decrypt(&encryptor, ciphertext, decrypted, ((strlen(data4) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    printf("Test 4: Original: %s, Decrypted: %s\\n", data4, decrypted);
    
    // Test case 5
    const char* data5 = "Account#: 7890123456";
    encrypt(&encryptor, (unsigned char*)data5, ciphertext, strlen(data5));
    decrypt(&encryptor, ciphertext, decrypted, ((strlen(data5) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    printf("Test 5: Original: %s, Decrypted: %s\\n", data5, decrypted);
    
    return 0;
}
