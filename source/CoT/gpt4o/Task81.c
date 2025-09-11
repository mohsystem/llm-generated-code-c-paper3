#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char *base64Encode(const unsigned char *input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length);
    memcpy(buff, bptr->data, bptr->length - 1);
    buff[bptr->length - 1] = 0;

    BIO_free_all(b64);

    return buff;
}

int checkSSLCertificate(const char *certificateContent, const char *knownHash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, certificateContent, strlen(certificateContent));
    SHA256_Final(hash, &sha256);

    char *encodedHash = base64Encode(hash, SHA256_DIGEST_LENGTH);
    int result = strcmp(encodedHash, knownHash) == 0;
    free(encodedHash);
    return result;
}

int main() {
    // Test cases
    const char *cert1 = "certificateContent1";
    const char *hash1 = "knownHash1";
    const char *cert2 = "certificateContent2";
    const char *hash2 = "knownHash2";
    const char *cert3 = "certificateContent3";
    const char *hash3 = "knownHash3";
    const char *cert4 = "certificateContent4";
    const char *hash4 = "knownHash4";
    const char *cert5 = "certificateContent5";
    const char *hash5 = "knownHash5";

    printf("%d\n", checkSSLCertificate(cert1, hash1)); // Output: 0
    printf("%d\n", checkSSLCertificate(cert2, hash2)); // Output: 0
    printf("%d\n", checkSSLCertificate(cert3, hash3)); // Output: 0
    printf("%d\n", checkSSLCertificate(cert4, hash4)); // Output: 0
    printf("%d\n", checkSSLCertificate(cert5, hash5)); // Output: 0

    return 0;
}