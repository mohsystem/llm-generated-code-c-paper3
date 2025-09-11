#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void base64_encode(const unsigned char* bytes_to_encode, unsigned int in_len, char* out) {
    BIO* bmem;
    BIO* b64;
    BUF_MEM* bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, bytes_to_encode, in_len);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    memcpy(out, bptr->data, bptr->length);
    out[bptr->length] = '\0';
    BIO_free_all(b64);
}

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char salt[16];
    RAND_bytes(salt, 16);

    unsigned char key[32];
    PKCS5_PBKDF2_HMAC_SHA1(password, strlen(password), salt, 16, 100000, 32, key);

    char salt_str[25];
    char key_str[45];
    base64_encode(salt, 16, salt_str);
    base64_encode(key, 32, key_str);
    sprintf(hashedPassword, "%s:%s", salt_str, key_str);
}

int verifyPassword(const char* originalPassword, const char* storedPassword) {
    char* colonPos = strchr(storedPassword, ':');
    if (colonPos == NULL) return 0;

    char salt_str[25];
    char key_str[45];
    strncpy(salt_str, storedPassword, colonPos - storedPassword);
    salt_str[colonPos - storedPassword] = '\0';
    strcpy(key_str, colonPos + 1);

    unsigned char salt[16];
    unsigned char key[32];
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* bmem = BIO_new_mem_buf(salt_str, strlen(salt_str));
    bmem = BIO_push(b64, bmem);
    int len = BIO_read(bmem, salt, 16);
    BIO_free_all(bmem);

    bmem = BIO_new_mem_buf(key_str, strlen(key_str));
    bmem = BIO_push(b64, bmem);
    len = BIO_read(bmem, key, 32);
    BIO_free_all(bmem);

    unsigned char testKey[32];
    PKCS5_PBKDF2_HMAC_SHA1(originalPassword, strlen(originalPassword), salt, 16, 100000, 32, testKey);

    return memcmp(key, testKey, 32) == 0;
}

int main() {
    char passwords[][20] = {"password123", "mysecret", "testpassword", "securepassword", "anotherpassword"};
    for (int i = 0; i < 5; ++i) {
        char hashedPassword[100];
        hashPassword(passwords[i], hashedPassword);
        printf("Password: %s, Hashed Password: %s\n", passwords[i], hashedPassword);
        printf("Verification: %s\n", verifyPassword(passwords[i], hashedPassword) ? "true" : "false");
    }
    return 0;
}