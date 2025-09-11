#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>

void encryptAES(const char* key, const char* data, unsigned char* encrypted) {
    unsigned char iv[EVP_MAX_IV_LENGTH];
    RAND_bytes(iv, sizeof(iv));

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (unsigned char*)key, iv);

    int len;
    EVP_EncryptUpdate(ctx, encrypted, &len, (unsigned char*)data, strlen(data));

    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, encrypted + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    char key[] = "examplekey123456";
    unsigned char encrypted[128];
    
    encryptAES(key, "TestCase1", encrypted);
    printf("TestCase1 Encrypted: %s\n", encrypted);
    encryptAES(key, "TestCase2", encrypted);
    printf("TestCase2 Encrypted: %s\n", encrypted);
    encryptAES(key, "TestCase3", encrypted);
    printf("TestCase3 Encrypted: %s\n", encrypted);
    encryptAES(key, "TestCase4", encrypted);
    printf("TestCase4 Encrypted: %s\n", encrypted);
    encryptAES(key, "TestCase5", encrypted);
    printf("TestCase5 Encrypted: %s\n", encrypted);

    return 0;
}