
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

void encrypt(const char* key, const char* data, unsigned char* encrypted, int* len) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    
    unsigned char iv[16] = {0};
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, 
                      (unsigned char*)key, iv);
    
    int temp_len;
    EVP_EncryptUpdate(ctx, encrypted, &temp_len,
                     (unsigned char*)data, strlen(data));
    
    *len = temp_len;
    EVP_EncryptFinal_ex(ctx, encrypted + temp_len, &temp_len);
    *len += temp_len;
    
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    const char* key = "1234567890123456"; // 16 byte key
    unsigned char encrypted[1024];
    int len;
    
    // Test Case 1
    encrypt(key, "Hello World", encrypted, &len);
    printf("Test Case 1: ");
    for(int i = 0; i < len; i++) printf("%02x", encrypted[i]);
    printf("\\n");
    
    // Test Case 2
    encrypt(key, "Testing123", encrypted, &len);
    printf("Test Case 2: ");
    for(int i = 0; i < len; i++) printf("%02x", encrypted[i]);
    printf("\\n");
    
    // Test Case 3
    encrypt(key, "SecureMessage", encrypted, &len);
    printf("Test Case 3: ");
    for(int i = 0; i < len; i++) printf("%02x", encrypted[i]);
    printf("\\n");
    
    // Test Case 4
    encrypt(key, "AES Encryption", encrypted, &len);
    printf("Test Case 4: ");
    for(int i = 0; i < len; i++) printf("%02x", encrypted[i]);
    printf("\\n");
    
    // Test Case 5
    encrypt(key, "CBC Mode Test", encrypted, &len);
    printf("Test Case 5: ");
    for(int i = 0; i < len; i++) printf("%02x", encrypted[i]);
    printf("\\n");
    
    return 0;
}
