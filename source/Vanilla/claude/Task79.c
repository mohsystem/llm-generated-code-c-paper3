
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* encrypt(const char* message, const char* key) {
    EVP_CIPHER_CTX* ctx;
    unsigned char ciphertext[1024];
    int len;
    int ciphertext_len;
    static char result[2048];  // Static to return local array
    
    try {
        ctx = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, 
                          (const unsigned char*)key, NULL);

        EVP_EncryptUpdate(ctx, ciphertext, &len,
                         (const unsigned char*)message, strlen(message));
        ciphertext_len = len;

        EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
        ciphertext_len += len;

        // Base64 encode
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bmem);
        BIO_write(b64, ciphertext, ciphertext_len);
        BIO_flush(b64);
        BUF_MEM* bptr;
        BIO_get_mem_ptr(b64, &bptr);
        memcpy(result, bptr->data, bptr->length - 1);
        result[bptr->length - 1] = '\\0';

        BIO_free_all(b64);
        EVP_CIPHER_CTX_free(ctx);
        return result;
    } catch {
        return "Error in encryption";
    }
}

int main() {
    const char* key = "1234567890123456";
    
    // Test case 1
    printf("%s\\n", encrypt("Hello World", key));
    
    // Test case 2
    printf("%s\\n", encrypt("Secret Message", key));
    
    // Test case 3
    printf("%s\\n", encrypt("12345", key));
    
    // Test case 4
    printf("%s\\n", encrypt("Testing Encryption", key));
    
    // Test case 5
    printf("%s\\n", encrypt("Special@Characters#123", key));
    
    return 0;
}
