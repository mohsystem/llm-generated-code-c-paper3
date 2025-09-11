
#include <stdio.h>
#include <string.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <ctype.h>

void bytes_to_hex(unsigned char* bytes, int len, char* hex) {
    for(int i = 0; i < len; i++) {
        sprintf(hex + (i * 2), "%02x", bytes[i]);
    }
    hex[len * 2] = '\\0';
}

int verify_certificate_hash(const char* cert_path, const char* expected_hash) {
    int result = 0;
    
    // Load certificate
    FILE* fp = fopen(cert_path, "r");
    if (!fp) return 0;
    
    X509* cert = PEM_read_X509(fp, NULL, NULL, NULL);
    fclose(fp);
    if (!cert) return 0;

    // Get DER encoding
    unsigned char* der = NULL;
    int der_len = i2d_X509(cert, &der);
    if (der_len < 0) {
        X509_free(cert);
        return 0;
    }

    // Calculate hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, der, der_len);
    SHA256_Final(hash, &sha256);

    // Convert to hex string
    char actual_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    bytes_to_hex(hash, SHA256_DIGEST_LENGTH, actual_hash);
    
    // Compare hashes (case insensitive)
    result = (strcasecmp(expected_hash, actual_hash) == 0);
    
    // Cleanup
    OPENSSL_free(der);
    X509_free(cert);
    
    return result;
}

int main() {
    const char* cert_path = "cert.pem";
    const char* test_hashes[] = {
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
        "a3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
        "b3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
        "c3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
        "d3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %d\\n", i+1, 
               verify_certificate_hash(cert_path, test_hashes[i]));
    }
    
    return 0;
}
