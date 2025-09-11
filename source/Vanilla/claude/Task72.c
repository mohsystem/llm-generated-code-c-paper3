
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#define MAX_ENCRYPTED_LEN 1024

static const unsigned char IV[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const unsigned char KEY[16] = {'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'};

char* encrypt(const char* input) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx)
        return NULL;
        
    if(EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, KEY, IV) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    
    unsigned char* encrypted = (unsigned char*)malloc(MAX_ENCRYPTED_LEN);
    int len1, len2;
    
    if(EVP_EncryptUpdate(ctx, encrypted, &len1, 
       (unsigned char*)input, strlen(input)) != 1) {
        free(encrypted);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    
    if(EVP_EncryptFinal_ex(ctx, encrypted + len1, &len2) != 1) {
        free(encrypted);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    
    EVP_CIPHER_CTX_free(ctx);
    
    // Convert to base64
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, encrypted, len1 + len2);
    BIO_flush(b64);
    
    BUF_MEM *bptr;
    BIO_get_mem_ptr(b64, &bptr);
    
    char* result = (char*)malloc(bptr->length);
    memcpy(result, bptr->data, bptr->length-1);
    result[bptr->length-1] = '\\0';
    
    BIO_free_all(b64);
    free(encrypted);
    
    return result;
}

int main() {
    const char* test_cases[] = {
        "Hello World",
        "Test123",
        "Encryption Example",
        "AES CBC Mode",
        "SecurityTest"
    };
    
    for(int i = 0; i < 5; i++) {
        char* encrypted = encrypt(test_cases[i]);
        if(encrypted) {
            printf("Test Case %d:\\n", i+1);
            printf("Input: %s\\n", test_cases[i]);
            printf("Encrypted: %s\\n\\n", encrypted);
            free(encrypted);
        } else {
            printf("Error encrypting test case %d\\n", i+1);
        }
    }
    
    return 0;
}
