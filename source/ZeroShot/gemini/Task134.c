#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// ... (Other functions: generate_key_pair, encrypt, decrypt as in previous response)

int main() {
    RSA *keypair = generate_key_pair(2048);
    if (!keypair) {
        fprintf(stderr, "Failed to generate key pair\n");
        return 1;
    }


    char *plaintext1 = "Test message 1";
    char *plaintext2 = "Test message 2 - slightly longer";
    char *plaintext3 = "Short";
    char *plaintext4 = "Special characters: !@#$%^&*()_+=-`~[]\';,./{}|:\"<>?";
    char *plaintext5 = "Another test";

    char *tests[] = {plaintext1, plaintext2, plaintext3, plaintext4, plaintext5};
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; i++) {
        unsigned char ciphertext[4098] = {0}; // Increased size
        int ciphertext_len = encrypt(tests[i], strlen(tests[i]), keypair, ciphertext);

        if (ciphertext_len == -1) {
             fprintf(stderr, "Encryption failed for test %d\n", i + 1);
            continue; // Skip to the next test
        }

        unsigned char decrypted[4098] = {0}; // Increased size
        int decrypted_len = decrypt(ciphertext, ciphertext_len, keypair, decrypted);

        if (decrypted_len == -1) {
            fprintf(stderr, "Decryption failed for test %d\n", i + 1);
            continue; // Skip to the next test
        }


        decrypted[decrypted_len] = '\0';
        printf("Plaintext: %s, Decrypted: %s\n", tests[i], decrypted);
    }

    RSA_free(keypair); // Free keypair after use
    return 0;
}




// generate_key_pair, encrypt, decrypt functions
RSA* generate_key_pair(int key_size) {
    BIGNUM* bne = BN_new();
    int ret = BN_set_word(bne, RSA_F4); // Public exponent 65537
    if (!ret) {
        BN_free(bne);
        return NULL; 
    }

    RSA* r = RSA_new();
    ret = RSA_generate_key_ex(r, key_size, bne, NULL); 
    BN_free(bne);

    if (!ret) {
        RSA_free(r);
        return NULL; 
    }
    return r;
}

int encrypt(const unsigned char *plaintext, int plaintext_len, RSA *keypair, unsigned char *ciphertext) {
    int ciphertext_len = RSA_public_encrypt(plaintext_len, plaintext, ciphertext, keypair, RSA_PKCS1_OAEP_PADDING);
    return ciphertext_len;
}


int decrypt(const unsigned char *ciphertext, int ciphertext_len, RSA *keypair, unsigned char *plaintext) {
  int plaintext_len = RSA_private_decrypt(ciphertext_len, ciphertext, plaintext, keypair, RSA_PKCS1_OAEP_PADDING);
  return plaintext_len;
}