
#include <stdio.h>
#include <string.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/sha.h>

int check_certificate_hash(const char* cert_path, const char* expected_hash) {
    // Load certificate
    FILE* fp = fopen(cert_path, "r");
    if (!fp) return 0;
    
    X509* cert = PEM_read_X509(fp, NULL, NULL, NULL);
    fclose(fp);
    if (!cert) return 0;

    // Calculate hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char* der = NULL;
    int der_len = i2d_X509(cert, &der);
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, der, der_len);
    SHA256_Final(hash, &sha256);
    
    OPENSSL_free(der);
    X509_free(cert);

    // Convert hash to hex string
    char calculated_hash[SHA256_DIGEST_LENGTH*2 + 1];
    calculated_hash[SHA256_DIGEST_LENGTH*2] = '\\0';
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&calculated_hash[i*2], "%02x", hash[i]);
    }

    // Compare hashes
    return strcmp(calculated_hash, expected_hash) == 0;
}

int main() {
    const char* certs[] = {
        "cert1.pem",
        "cert2.pem",
        "cert3.pem",
        "cert4.pem",
        "cert5.pem"
    };
    
    const char* hashes[] = {
        "a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6",
        "b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6a1",
        "c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6a1b2",
        "d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6a1b2c3",
        "e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6a1b2c3d4"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %d\\n", i+1, 
               check_certificate_hash(certs[i], hashes[i]));
    }
    
    return 0;
}
