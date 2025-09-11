
#include <stdio.h>
#include <string.h>
#include <openssl/x509.h>
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <ctype.h>
#include <stdbool.h>

void bytesToHexString(unsigned char* bytes, size_t length, char* output) {
    for(size_t i = 0; i < length; i++) {
        sprintf(output + (i * 2), "%02x", bytes[i]);
    }
}

bool checkCertificateHash(const char* certPath, const char* expectedHash) {
    bool result = false;
    
    // Read certificate
    FILE* fp = fopen(certPath, "r");
    if (!fp) return false;
    
    X509* cert = PEM_read_X509(fp, NULL, NULL, NULL);
    fclose(fp);
    if (!cert) return false;

    // Calculate hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char* der = NULL;
    int der_len = i2d_X509(cert, &der);
    
    if (der_len >= 0) {
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, der, der_len);
        SHA256_Final(hash, &sha256);

        // Convert hash to hex string
        char calculatedHash[SHA256_DIGEST_LENGTH * 2 + 1] = {0};
        bytesToHexString(hash, SHA256_DIGEST_LENGTH, calculatedHash);
        
        // Compare hashes (case insensitive)
        result = (strcasecmp(calculatedHash, expectedHash) == 0);
        
        OPENSSL_free(der);
    }
    
    X509_free(cert);
    return result;
}

int main() {
    const char* certPath = "test.crt"; // Replace with actual cert path
    const char* testHashes[] = {
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", // Valid
        "a3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", // Invalid
        "b3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", // Invalid
        "c3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", // Invalid
        "d3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"  // Invalid
    };

    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %s\\n", i+1, 
               checkCertificateHash(certPath, testHashes[i]) ? "true" : "false");
    }
    
    return 0;
}
