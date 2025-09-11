#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

unsigned char* encrypt(const unsigned char* data, int data_len, const unsigned char* key, int* encrypted_len) {
    unsigned char iv[16];
    RAND_bytes(iv, sizeof(iv));

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char* encrypted = (unsigned char*)malloc(data_len + 16);
    int len;
    EVP_EncryptUpdate(ctx, encrypted, &len, data, data_len);
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, encrypted + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    *encrypted_len = ciphertext_len + sizeof(iv);
    unsigned char* result = (unsigned char*)malloc(*encrypted_len);
    memcpy(result, encrypted, ciphertext_len);
    memcpy(result + ciphertext_len, iv, sizeof(iv));

    free(encrypted);
    return result;
}

unsigned char* decrypt(const unsigned char* encrypted_data, int encrypted_len, const unsigned char* key, int* decrypted_len) {
    unsigned char iv[16];
    memcpy(iv, encrypted_data + encrypted_len - sizeof(iv), sizeof(iv));

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char* decrypted = (unsigned char*)malloc(encrypted_len);
    int len;
    EVP_DecryptUpdate(ctx, decrypted, &len, encrypted_data, encrypted_len - sizeof(iv));
    int plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, decrypted + len, &len);
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    *decrypted_len = plaintext_len;
    return decrypted;
}

unsigned char* generateKey() {
    unsigned char* key = (unsigned char*)malloc(32);
    RAND_bytes(key, 32);
    return key;
}

int main() {
    unsigned char* key = generateKey();

    const unsigned char data1[] = "Test data 1";
    int encrypted_len1, decrypted_len1;
    unsigned char* encrypted_data1 = encrypt(data1, strlen((char*)data1), key, &encrypted_len1);
    unsigned char* decrypted_data1 = decrypt(encrypted_data1, encrypted_len1, key, &decrypted_len1);
    printf("%.*s\n", decrypted_len1, decrypted_data1);
    free(encrypted_data1);
    free(decrypted_data1);

    const unsigned char data2[] = "Test data 2";
    int encrypted_len2, decrypted_len2;
    unsigned char* encrypted_data2 = encrypt(data2, strlen((char*)data2), key, &encrypted_len2);
    unsigned char* decrypted_data2 = decrypt(encrypted_data2, encrypted_len2, key, &decrypted_len2);
    printf("%.*s\n", decrypted_len2, decrypted_data2);
    free(encrypted_data2);
    free(decrypted_data2);

    const unsigned char data3[] = "Test data 3";
    int encrypted_len3, decrypted_len3;
    unsigned char* encrypted_data3 = encrypt(data3, strlen((char*)data3), key, &encrypted_len3);
    unsigned char* decrypted_data3 = decrypt(encrypted_data3, encrypted_len3, key, &decrypted_len3);
    printf("%.*s\n", decrypted_len3, decrypted_data3);
    free(encrypted_data3);
    free(decrypted_data3);

    const unsigned char data4[] = "Test data 4";
    int encrypted_len4, decrypted_len4;
    unsigned char* encrypted_data4 = encrypt(data4, strlen((char*)data4), key, &encrypted_len4);
    unsigned char* decrypted_data4 = decrypt(encrypted_data4, encrypted_len4, key, &decrypted_len4);
    printf("%.*s\n", decrypted_len4, decrypted_data4);
    free(encrypted_data4);
    free(decrypted_data4);

    const unsigned char data5[] = "Test data 5";
    int encrypted_len5, decrypted_len5;
    unsigned char* encrypted_data5 = encrypt(data5, strlen((char*)data5), key, &encrypted_len5);
    unsigned char* decrypted_data5 = decrypt(encrypted_data5, encrypted_len5, key, &decrypted_len5);
    printf("%.*s\n", decrypted_len5, decrypted_data5);
    free(encrypted_data5);
    free(decrypted_data5);

    free(key);
    return 0;
}