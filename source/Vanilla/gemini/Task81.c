#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>


// ... (Rest of the C code as in the previous response)

bool verifySSLCertificateHash(const char* certPath, const char* expectedHash, const char* algorithm) {

    // OpenSSL initialization (required for OpenSSL 3.0 and later)
    OpenSSL_add_all_algorithms();

    BIO *certbio = BIO_new(BIO_s_file());
    BIO_read_filename(certbio, certPath);
    X509 *cert = PEM_read_bio_X509(certbio, NULL, 0, NULL);
    BIO_free_all(certbio);

    if (!cert) {
        fprintf(stderr, "Error loading certificate.\n");
        return false;
    }

    unsigned char certHash[EVP_MAX_MD_SIZE];
    unsigned int certHashLen = 0;

    const EVP_MD *md = EVP_get_digestbyname(algorithm);
    if (!md) {
        X509_free(cert);
        fprintf(stderr, "Error getting digest algorithm.\n");
        return false;
    }

    if (!X509_digest(cert, md, certHash, &certHashLen)) {
        X509_free(cert);
        fprintf(stderr, "Error calculating hash.\n");
        return false;
    }

    X509_free(cert);

    char calculatedHash[2*certHashLen + 1];
    for (unsigned int i = 0; i < certHashLen; ++i) {
        sprintf(calculatedHash + (i * 2), "%02x", certHash[i]);
    }
    calculatedHash[2 * certHashLen] = '\0';


    return strcmp(expectedHash, calculatedHash) == 0;

}

int main() {
    // Test cases (replace with actual certificate paths and hashes)
    char* certPath1 = "path/to/certificate1.crt";
    char* expectedHash1 = "expected_hash_1";
    char* algorithm1 = "sha256";

    // ... (Define certificate paths and expected hashes for tests 2-5 similarly)


    bool result1 = verifySSLCertificateHash(certPath1, expectedHash1, algorithm1);
    printf("Test 1: %s\n", result1 ? "true" : "false");


        // OpenSSL cleanup (required for OpenSSL 3.0 and later)
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    return 0;
}