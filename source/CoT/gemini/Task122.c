#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


char* base64_encode(const unsigned char* data, size_t len) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *mem = BIO_new(BIO_s_mem());
    BIO_push(b64, mem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, data, len);
    BIO_flush(b64);
    BUF_MEM *bptr;
    BIO_get_mem_ptr(mem, &bptr);
    char *result = (char*)malloc(bptr->length + 1);
    memcpy(result, bptr->data, bptr->length);
    result[bptr->length] = '\0';
    BIO_free_all(b64);
    return result;

}


char* hash_password(const char* password) {

    unsigned char salt[16];

    FILE *fp = fopen("/dev/random", "r");
    if (fp == NULL) {
        perror("Error opening /dev/random");
        return NULL; 
    }
    size_t bytes_read = fread(salt, sizeof(unsigned char), 16, fp);
    if (bytes_read != 16) {
        fprintf(stderr, "Error reading enough random bytes\n");
        fclose(fp);
        return NULL;
    }
    fclose(fp);



    unsigned char hash[SHA256_DIGEST_LENGTH];
    PKCS5_PBKDF2_HMAC_SHA1(password, strlen(password), salt, 16, 100000, SHA256_DIGEST_LENGTH, hash);

    char *salt_b64 = base64_encode(salt, 16);
    char *hash_b64 = base64_encode(hash, SHA256_DIGEST_LENGTH);


    char* result = (char*) malloc(strlen(salt_b64) + strlen(hash_b64) + 2); 
    strcpy(result, salt_b64);
    strcat(result, ":");
    strcat(result, hash_b64);

    free(salt_b64);
    free(hash_b64);

    return result;
}


int verify_password(const char* password, const char* stored_hash) {

    char *stored_hash_copy = strdup(stored_hash);

    char* salt_b64 = strtok(stored_hash_copy, ":");
    char *hash_b64 = strtok(NULL, ":");


    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *mem = BIO_new_mem_buf(salt_b64, strlen(salt_b64));
    BIO_push(b64, mem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    unsigned char salt[16];
    BIO_read(b64, salt, 16);
    BIO_free_all(b64);


    unsigned char hash[SHA256_DIGEST_LENGTH];
    PKCS5_PBKDF2_HMAC_SHA1(password, strlen(password), salt, 16, 100000, SHA256_DIGEST_LENGTH, hash);
    char *calculated_hash_b64 = base64_encode(hash, SHA256_DIGEST_LENGTH);

    int result = strcmp(calculated_hash_b64, hash_b64) == 0;


    free(stored_hash_copy);
    free(calculated_hash_b64);


    return result;
}

int main() {
    char *passwords[] = {"password123", "test", "securepassword", "123456", "complexPassword!"};
    int num_passwords = sizeof(passwords) / sizeof(passwords[0]);

    for (int i = 0; i < num_passwords; i++) {
        char *hashed_password = hash_password(passwords[i]);
        printf("Hashed Password: %s\n", hashed_password);
        printf("Verification: %d\n", verify_password(passwords[i], hashed_password));

        free(hashed_password); 
    }

    return 0;
}