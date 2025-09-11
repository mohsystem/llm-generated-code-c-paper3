#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* generate_salt() {
    unsigned char salt[16];
    RAND_bytes(salt, sizeof(salt));
    EVP_EncodeBuffer(nullptr, nullptr, salt, sizeof(salt));
    return strdup(reinterpret_cast<char*>(salt));
}

char* hash_password(const char* password, const char* salt) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_get_digestbyname("SHA256");
    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, salt, strlen(salt));
    EVP_DigestUpdate(mdctx, password, strlen(password));
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);
    EVP_EncodeBuffer(nullptr, nullptr, hash, hash_len);
    return strdup(reinterpret_cast<char*>(hash));
}

int main() {
    const char* passwords[5] = {"password1", "password2", "password3", "password4", "password5"};
    for (int i = 0; i < 5; i++) {
        char* salt = generate_salt();
        char* hashed_password = hash_password(passwords[i], salt);
        printf("Password: %s, Salt: %s, Hashed Password: %s\n", passwords[i], salt, hashed_password);
        free(salt);
        free(hashed_password);
    }
    return 0;
}