
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#define MAX_BUFFER_SIZE 1024

const unsigned char key[] = "ThisIsA128BitKey";

char* encrypt(const char* data, int* outlen) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    unsigned char* encrypted = malloc(MAX_BUFFER_SIZE);
    int len1, len2;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_EncryptUpdate(ctx, encrypted, &len1, (unsigned char*)data, strlen(data));
    EVP_EncryptFinal_ex(ctx, encrypted + len1, &len2);
    
    *outlen = len1 + len2;
    EVP_CIPHER_CTX_free(ctx);
    return (char*)encrypted;
}

char* decrypt(const unsigned char* encrypted_data, int inlen, int* outlen) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    unsigned char* decrypted = malloc(MAX_BUFFER_SIZE);
    int len1, len2;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_DecryptUpdate(ctx, decrypted, &len1, encrypted_data, inlen);
    EVP_DecryptFinal_ex(ctx, decrypted + len1, &len2);
    
    *outlen = len1 + len2;
    decrypted[*outlen] = '\\0';
    EVP_CIPHER_CTX_free(ctx);
    return (char*)decrypted;
}

char* base64_encode(const unsigned char* input, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char* encoded = malloc(bufferPtr->length);
    memcpy(encoded, bufferPtr->data, bufferPtr->length-1);
    encoded[bufferPtr->length-1] = '\\0';

    BIO_free_all(bio);
    return encoded;
}

unsigned char* base64_decode(const char* input, int* outlen) {
    BIO *bio, *b64;
    unsigned char* buffer = malloc(MAX_BUFFER_SIZE);

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(input, -1);
    bio = BIO_push(b64, bio);

    *outlen = BIO_read(bio, buffer, strlen(input));
    BIO_free_all(bio);

    return buffer;
}

int main() {
    // Test case 1
    const char* text1 = "Hello World";
    int encrypted_len1;
    char* encrypted1 = encrypt(text1, &encrypted_len1);
    char* base64_1 = base64_encode((unsigned char*)encrypted1, encrypted_len1);
    printf("Test 1 - Original: %s\\n", text1);
    printf("Encrypted (Base64): %s\\n", base64_1);
    
    int decoded_len1;
    unsigned char* decoded1 = base64_decode(base64_1, &decoded_len1);
    int decrypted_len1;
    char* decrypted1 = decrypt(decoded1, decoded_len1, &decrypted_len1);
    printf("Decrypted: %s\\n\\n", decrypted1);

    // Test case 2
    const char* text2 = "Sensitive Data 123";
    int encrypted_len2;
    char* encrypted2 = encrypt(text2, &', type='text')