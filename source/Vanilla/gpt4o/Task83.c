#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>

void encryptAES(const char *key, char *output) {
    // Generate AES key
    unsigned char secret_key[16];
    RAND_bytes(secret_key, sizeof(secret_key));

    // Initialize cipher in CBC mode with a random IV
    unsigned char iv[16];
    RAND_bytes(iv, sizeof(iv));

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, secret_key, iv);

    // Encrypt the key
    int len;
    int ciphertext_len;
    unsigned char encrypted[128];
    EVP_EncryptUpdate(ctx, encrypted, &len, (unsigned char*)key, strlen(key));
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, encrypted + len, &len);
    ciphertext_len += len;

    // Convert encrypted data to hexadecimal
    for (int i = 0; i < ciphertext_len; i++) {
        sprintf(output + i * 2, "%02x", encrypted[i]);
    }

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    char output[256];
    encryptAES("This is a test key 1", output);
    printf("%s\n", output);

    encryptAES("This is a test key 2", output);
    printf("%s\n", output);

    encryptAES("This is a test key 3", output);
    printf("%s\n", output);

    encryptAES("This is a test key 4", output);
    printf("%s\n", output);

    encryptAES("This is a test key 5", output);
    printf("%s\n", output);

    return 0;
}