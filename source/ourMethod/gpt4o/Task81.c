#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>

int isCertHashMatching(const char* certString, const char* knownHash) {
    BIO* bio = BIO_new_mem_buf(certString, strlen(certString));
    if (!bio) return 0;
    
    X509* cert = d2i_X509_bio(bio, NULL);
    BIO_free(bio);
    
    if (!cert) return 0;
    
    unsigned char certHash[SHA256_DIGEST_LENGTH];
    unsigned int hashLen;
    if (!X509_digest(cert, EVP_sha256(), certHash, &hashLen)) {
        X509_free(cert);
        return 0;
    }
    X509_free(cert);

    char hashStr[SHA256_DIGEST_LENGTH*2+1];
    for (unsigned int i = 0; i < hashLen; i++) {
        sprintf(&hashStr[i*2], "%02x", certHash[i]);
    }
    
    return strcmp(knownHash, hashStr) == 0;
}

int main() {
    // Test Cases
    printf("%d\n", isCertHashMatching("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA...", "knownhash1"));
    printf("%d\n", isCertHashMatching("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEB...", "knownhash2"));
    printf("%d\n", isCertHashMatching("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEC...", "knownhash3"));
    printf("%d\n", isCertHashMatching("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQED...", "knownhash4"));
    printf("%d\n", isCertHashMatching("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEE...", "knownhash5"));
    return 0;
}