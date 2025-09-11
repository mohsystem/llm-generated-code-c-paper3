#include <stdio.h>
#include <string.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/err.h>

// Helper function to calculate the hash (similar to C++ version)
bool calculate_hash(X509 *certificate, const char *hashAlgorithm, unsigned char *calculatedHash, unsigned int *calculatedHashLength) {
    if (strcmp(hashAlgorithm, "SHA-256") == 0 || strcmp(hashAlgorithm, "sha256") == 0) {
        *calculatedHashLength = SHA256_DIGEST_LENGTH;
        SHA256(certificate->cert_info->signature->data, certificate->cert_info->signature->length, calculatedHash);
        return true;
    } else if (strcmp(hashAlgorithm, "SHA-1") == 0 || strcmp(hashAlgorithm, "sha1") == 0) {
        *calculatedHashLength = SHA_DIGEST_LENGTH;
        SHA1(certificate->cert_info->signature->data, certificate->cert_info->signature->length, calculatedHash);
        return true;
    } else {
        return false; // Unsupported algorithm
    }
}


bool verifyCertificateHash(const char *certificatePath, const char *expectedHash, const char *hashAlgorithm) {
    FILE *certFile = fopen(certificatePath, "rb");
    if (!certFile) {
        fprintf(stderr, "Could not open certificate file: %s\n", certificatePath);
        return false;
    }
    X509 *certificate = PEM_read_X509(certFile, NULL, NULL, NULL);
    fclose(certFile);

    if (!certificate) {
        fprintf(stderr, "Failed to read certificate\n");
        return false;
    }

    unsigned char calculatedHash[SHA256_DIGEST_LENGTH];
    unsigned int calculatedHashLength;
    if (!calculate_hash(certificate, hashAlgorithm, calculatedHash, &calculatedHashLength)) {
        fprintf(stderr, "Unsupported hash algorithm: %s\n", hashAlgorithm);
        X509_free(certificate);
        return false;
    }


    BIO *hashbio = BIO_new(BIO_s_mem());
    BIO_set_flags(hashbio, BIO_FLAGS_BASE64_NO_NL);
    BIO *b64 = BIO_new(BIO_f_base64());
    hashbio = BIO_push(b64, hashbio);
    BIO_write(hashbio, calculatedHash, calculatedHashLength);
    BIO_flush(hashbio);

    char *hashptr = NULL;
    long hashlen = BIO_get_mem_data(hashbio, &hashptr);
    char calculatedHashString[hashlen+1];
    strncpy(calculatedHashString, hashptr, hashlen);
    calculatedHashString[hashlen] = '\0';


    BIO_free_all(hashbio);
    X509_free(certificate);
    

    return strcmp(calculatedHashString, expectedHash) == 0;

}

int main() {
    char *certPath = "test.cer";

    printf("%d\n", verifyCertificateHash(certPath, "asdasd", "SHA-256"));
    printf("%d\n", verifyCertificateHash(certPath, "asdasdasd", "SHA-256"));
    printf("%d\n", verifyCertificateHash(certPath, "121212121212", "SHA-256"));
    printf("%d\n", verifyCertificateHash(certPath, "asdasd54545", "SHA-256"));
    printf("%d\n", verifyCertificateHash(certPath, "////////////////", "SHA-256"));
    return 0;
}