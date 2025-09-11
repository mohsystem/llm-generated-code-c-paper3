#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <string.h>
#include <stdio.h>

void encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char *key = (unsigned char *)"01234567890123456789012345678912";
    unsigned char *iv = (unsigned char *)"0123456789012345";
    unsigned char *plaintext = (unsigned char *)"Hello, World!";
    unsigned char ciphertext[128];

    encrypt(plaintext, strlen((char *)plaintext), key, iv, ciphertext);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO *out = BIO_new_fp(stdout, BIO_NOCLOSE);
    bio = BIO_push(bio, out);
    BIO_write(bio, ciphertext, strlen((char *)ciphertext));
    BIO_flush(bio);
    BIO_free_all(bio);

    return 0;
}