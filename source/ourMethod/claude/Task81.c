
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

#define MAX_HASH_LEN 256
#define BUFFER_SIZE 8192

int verify_certificate_hash(const unsigned char* certificate_data, 
                          size_t cert_len,
                          const char* expected_hash) {
    if (!certificate_data || !expected_hash || cert_len == 0 || strlen(expected_hash) == 0) {
        return 0;
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char computed_hash[MAX_HASH_LEN] = {0};
    char expected_hash_lower[MAX_HASH_LEN] = {0};
    size_t i;
    
    // Verify input lengths
    if (strlen(expected_hash) >= MAX_HASH_LEN) {
        return 0;
    }
    
    // Generate SHA-256 hash
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) {
        return 0;
    }
    if (!SHA256_Update(&sha256, certificate_data, cert_len)) {
        return 0;
    }
    if (!SHA256_Final(hash, &sha256)) {
        return 0;
    }
    
    // Convert hash to hex string
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        snprintf(&computed_hash[i*2], 3, "%02x", hash[i]);
    }
    
    // Convert expected hash to lowercase for comparison
    strncpy(expected_hash_lower, expected_hash, MAX_HASH_LEN - 1);
    for (i = 0; expected_hash_lower[i]; i++) {
        expected_hash_lower[i] = tolower((unsigned char)expected_hash_lower[i]);
    }
    
    // Compare hashes
    return strcmp(computed_hash, expected_hash_lower) == 0;
}

int main() {
    const char* expected_hash = "a1b2c3d4e5f6g7h8i9j0"; // Example hash
    unsigned char cert_buffer[BUFFER_SIZE];
    size_t cert_size;
    FILE* cert_file;
    
    // Test case 1: Valid certificate with matching hash
    cert_file = fopen("test_cert.cer", "rb");
    if (cert_file) {
        cert_size = fread(cert_buffer, 1, BUFFER_SIZE, cert_file);
        printf("Test 1: %d\\n", 
            verify_certificate_hash(cert_buffer, cert_size, expected_hash));
        fclose(cert_file);
    }
    
    // Test case 2: Null certificate
    printf("Test 2: %d\\n", 
        verify_certificate_hash(NULL, 0, expected_hash));
    
    // Test case 3: Null hash
    printf("Test 3: %d\\n", 
        verify_certificate_hash(cert_buffer, cert_size, NULL));
    
    // Test case 4: Empty hash
    printf("Test 4: %d\\n", 
        verify_certificate_hash(cert_buffer, cert_size, ""));
    
    // Test case 5: Invalid certificate data
    unsigned char invalid_cert[] = {1, 2, 3};
    printf("Test 5: %d\\n", 
        verify_certificate_hash(invalid_cert, 3, expected_hash));
    
    return 0;
}
