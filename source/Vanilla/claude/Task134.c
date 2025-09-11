
#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// Function to generate RSA key pair
RSA* generate_key_pair() {
    RSA *rsa = RSA_new();
    BIGNUM *bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bn, NULL);
    BN_free(bn);
    return rsa;
}

// Function to encode key to base64 string
char* encode_key(RSA* rsa, int is_private) {
    BIO *bio = BIO_new(BIO_s_mem());
    if (is_private) {
        PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    } else {
        PEM_write_bio_RSA_PUBKEY(bio, rsa);
    }
    
    BUF_MEM *bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    
    char* result = (char*)malloc(bufferPtr->length + 1);
    memcpy(result, bufferPtr->data, bufferPtr->length);
    result[bufferPtr->length] = '\\0';
    
    BIO_free_all(bio);
    return result;
}

// Function to verify key pair
int verify_key_pair(RSA* rsa) {
    const char* test_message = "Test Message";
    unsigned char encrypted[256];
    unsigned char decrypted[256];
    
    int encrypted_length = RSA_public_encrypt(
        strlen(test_message),
        (unsigned char*)test_message,
        encrypted,
        rsa,
        RSA_PKCS1_PADDING
    );
    
    if (encrypted_length == -1) return 0;
    
    int decrypted_length = RSA_private_decrypt(
        encrypted_length,
        encrypted,
        decrypted,
        rsa,
        RSA_PKCS1_PADDING
    );
    
    if (decrypted_length == -1) return 0;
    
    return (memcmp(test_message, decrypted, decrypted_length) == 0);
}

int main() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // Test Case 1: Generate and verify key pair
    RSA* key_pair1 = generate_key_pair();
    printf("Test 1 - Key pair generated and verified: %d\\n", verify_key_pair(key_pair1));
    
    // Test Case 2: Encode public key
    char* encoded_public = encode_key(key_pair1, 0);
    printf("Test 2 - Encoded public key length: %lu\\n", strlen(encoded_public));
    
    // Test Case 3: Encode private key
    char* encoded_private = encode_key(key_pair1, 1);
    printf("Test 3 - Encoded private key length: %lu\\n", strlen(encoded_private));
    
    // Test Case 4: Generate different key pairs
    RSA* key_pair2 = generate_key_pair();
    char* encoded_public2 = encode_key(key_pair2, 0);
    printf("Test 4 - Different key pairs are unique: %d\\n", 
           strcmp(encoded_public, encoded_public2) != 0);
    
    // Test Case 5: Verify another key pair
    printf("Test 5 - Second key pair verified: %d\\n", verify_key_pair(key_pair2));
    
    // Cleanup
    free(encoded_public);
    free(encoded_private);
    free(encoded_public2);
    RSA_free(key_pair1);
    RSA_free(key_pair2);
    EVP_cleanup();
    ERR_free_strings();
    
    return 0;
}
