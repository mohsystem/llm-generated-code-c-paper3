// C code requires external library like OpenSSL or Crypto++
// Below is a basic example using OpenSSL

#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

void encrypt(const char* input, unsigned char* encrypted_data) {
    unsigned char key[AES_KEY_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];

    RAND_bytes(key, AES_KEY_SIZE);
    RAND_bytes(iv, AES_BLOCK_SIZE);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv);

    int out_len1 = 0;
    EVP_EncryptUpdate(ctx, encrypted_data, &out_len1, (const unsigned char*)input, strlen(input));

    int out_len2 = 0;
    EVP_EncryptFinal_ex(ctx, encrypted_data + out_len1, &out_len2);

    EVP_CIPHER_CTX_free(ctx);

    memcpy(encrypted_data, iv, AES_BLOCK_SIZE);
}

int main() {
    const char* test_cases[] = {"Hello, World!", "Test Case 2", "This is a longer test case.", "", " "};
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        unsigned char encrypted_data[AES_BLOCK_SIZE + strlen(test_cases[i])];
        encrypt(test_cases[i], encrypted_data);

        printf("Original: %s\n", test_cases[i]);
        printf("Encrypted: ");
        for (int j = 0; j < AES_BLOCK_SIZE + strlen(test_cases[i]); j++) {
            printf("%02x", encrypted_data[j]);
        }
        printf("\n\n");
    }

    return 0;
}