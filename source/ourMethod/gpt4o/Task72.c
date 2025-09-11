#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

unsigned char* encrypt_data(const unsigned char* data, int data_len, const unsigned char* key, int* out_len) {
    if (!key || (strlen((const char*)key) != 16 && strlen((const char*)key) != 24 && strlen((const char*)key) != 32)) {
        fprintf(stderr, "Invalid key size.\n");
        return NULL;
    }

    // Create a static IV
    unsigned char iv[16];
    RAND_bytes(iv, sizeof(iv));

    // Initialize cipher
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Encrypt data
    int len;
    int ciphertext_len;
    unsigned char* encrypted_data = (unsigned char*)malloc(data_len + 16);
    EVP_EncryptUpdate(ctx, encrypted_data, &len, data, data_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, encrypted_data + len, &len);
    ciphertext_len += len;

    // Combine IV and encrypted data for output
    unsigned char* combined_data = (unsigned char*)malloc(sizeof(iv) + ciphertext_len);
    memcpy(combined_data, iv, sizeof(iv));
    memcpy(combined_data + sizeof(iv), encrypted_data, ciphertext_len);

    EVP_CIPHER_CTX_free(ctx);
    free(encrypted_data);

    *out_len = sizeof(iv) + ciphertext_len;
    return combined_data;
}

int main() {
    unsigned char key[16]; // 128-bit key
    RAND_bytes(key, sizeof(key));

    const unsigned char* data1 = (unsigned char*)"Hello World 1";
    const unsigned char* data2 = (unsigned char*)"Hello World 2";
    const unsigned char* data3 = (unsigned char*)"Hello World 3";
    const unsigned char* data4 = (unsigned char*)"Hello World 4";
    const unsigned char* data5 = (unsigned char*)"Hello World 5";

    int out_len;
    unsigned char* encrypted1 = encrypt_data(data1, strlen((const char*)data1), key, &out_len);
    unsigned char* encrypted2 = encrypt_data(data2, strlen((const char*)data2), key, &out_len);
    unsigned char* encrypted3 = encrypt_data(data3, strlen((const char*)data3), key, &out_len);
    unsigned char* encrypted4 = encrypt_data(data4, strlen((const char*)data4), key, &out_len);
    unsigned char* encrypted5 = encrypt_data(data5, strlen((const char*)data5), key, &out_len);

    for (int i = 0; i < out_len; i++) printf("%02x", encrypted1[i]);
    printf("\n");
    for (int i = 0; i < out_len; i++) printf("%02x", encrypted2[i]);
    printf("\n");
    for (int i = 0; i < out_len; i++) printf("%02x", encrypted3[i]);
    printf("\n");
    for (int i = 0; i < out_len; i++) printf("%02x", encrypted4[i]);
    printf("\n");
    for (int i = 0; i < out_len; i++) printf("%02x", encrypted5[i]);
    printf("\n");

    free(encrypted1);
    free(encrypted2);
    free(encrypted3);
    free(encrypted4);
    free(encrypted5);

    return 0;
}