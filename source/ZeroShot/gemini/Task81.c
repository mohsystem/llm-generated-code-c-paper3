#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>



//  Mostly the same as the C++ version.  See comments there.

bool verifyCertificateHash(const char* certificatePath, const char* expectedHash) {
    FILE *certFile = fopen(certificatePath, "rb");
    if (!certFile) {
        fprintf(stderr, "Error opening certificate file: %s\n", certificatePath);
        return false;
    }

    BIO* certbio = BIO_new(BIO_s_file());
    if (!certbio) {
         fprintf(stderr, "BIO_new failed\n");
        fclose(certFile);
        return false;
    }

    BIO_set_fp(certbio, certFile, BIO_NOCLOSE); // BIO takes ownership

    X509* cert = PEM_read_bio_X509_AUX(certbio, NULL, NULL, NULL);
    
    if (!cert) {
         fprintf(stderr, "PEM_read_bio_X509 failed\n");
         BIO_free(certbio); // This will close the file as well.
         return false;
    }

    unsigned char calculatedHash[SHA256_DIGEST_LENGTH];
    int len = i2d_X509(cert, NULL);
    if (len < 0) {
        fprintf(stderr, "i2d_X509 failed\n");
        X509_free(cert);
        BIO_free(certbio);
        return false;
    }


    unsigned char* x509_buffer = (unsigned char*)malloc(len);
    unsigned char* p = x509_buffer;

    len = i2d_X509(cert, &p);

    SHA256(x509_buffer, len, calculatedHash);

    char calculatedHashHex[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(calculatedHashHex + (i * 2), "%02x", calculatedHash[i]);
    }

    calculatedHashHex[SHA256_DIGEST_LENGTH * 2] = 0;


    bool match = (strcasecmp(calculatedHashHex, expectedHash) == 0);
    free(x509_buffer);
    X509_free(cert);
    BIO_free(certbio); // This will close the file.

    return match;

}

int main() {
    // Test cases (replace with actual certificate paths and hash values)
    const char* certPath1 = "path/to/certificate.pem"; // Replace with your certificate file path.
    const char* expectedHash1 = "expected_hash_of_certificate";  // Replace with the expected hash


    printf("Test 1: %s\n", verifyCertificateHash(certPath1, expectedHash1) ? "true" : "false");
    // ... Add more test cases ...

    return 0;
}