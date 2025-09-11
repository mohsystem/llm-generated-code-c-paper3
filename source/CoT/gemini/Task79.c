//  C code implementation will be similar to C++, utilizing OpenSSL for AES encryption.  
//  Include necessary headers (openssl/aes.h, openssl/rand.h, openssl/evp.h, openssl/err.h, string.h, stdio.h, stdlib.h),
//  and a base64 encoding library if available.
// The structure and logic will largely mirror the C++ example, including key handling, IV generation,
//  AES encryption with CBC mode, and Base64 encoding of the ciphertext. Adapt the C++ code provided above to C,
//  paying attention to memory management and string handling differences.  Provide error handling and test cases as shown in the other examples.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <base64.h> // Assuming you have a base64 encoding library



char* encryptMessage(const char* message, const char* secretKey) {
    try {
         // Ensure key is 32 bytes (256 bits for AES-256)
        unsigned char key[32];
        if (strlen(secretKey) >= 32) {
            strncpy((char *)key, secretKey, 32);
        } else {
            strcpy((char *)key, secretKey);
            // Pad with zeros if needed
            for(int i=strlen(secretKey);i<32;i++)
                key[i]=0;
        }

        AES_KEY aesKey;
        if (AES_set_encrypt_key(key, 256, &aesKey) < 0) {
            // Handle error appropriately (e.g., return NULL or error code)
             perror("Failed to set encryption key.");
            return NULL; 
        }

        int messageLen = strlen(message);
        int ciphertextLen = messageLen + AES_BLOCK_SIZE; // Account for padding
        unsigned char *ciphertext = (unsigned char *)malloc(ciphertextLen * sizeof(unsigned char));
        unsigned char iv[AES_BLOCK_SIZE]; // Initialization Vector (IV) - use a secure random IV

        RAND_bytes(iv, AES_BLOCK_SIZE); // Generate a random IV

        AES_cbc_encrypt((unsigned char*)message, ciphertext, messageLen, &aesKey, iv, AES_ENCRYPT);

        // Encode the IV and ciphertext using Base64
        char *base64Ciphertext = base64_encode(ciphertext, ciphertextLen);
        free(ciphertext);
        return base64Ciphertext;

    } catch (const char* e) {
        // Handle errors
        fprintf(stderr, "Error: %s\n", e);
        return NULL;
    }
}


int main() {
    char *message1 = "This is a secret message.";
    char *key1 = "MySecretKey123";
    char *encrypted1 = encryptMessage(message1, key1);
    if (encrypted1) {
        printf("Encrypted Message 1: %s\n", encrypted1);
        free(encrypted1); // Free allocated memory
    }


    char *message2 = "Another message to encrypt.";
    char *key2 = "ASecretKey";
    char *encrypted2 = encryptMessage(message2, key2);
    if (encrypted2) {
        printf("Encrypted Message 2: %s\n", encrypted2);
        free(encrypted2); 
    }



    char *message3 = "short message";
    char *key3 = "key123";
    char *encrypted3 = encryptMessage(message3, key3);
    if (encrypted3) {
        printf("Encrypted Message 3: %s\n", encrypted3);
        free(encrypted3); 
    }

    char *message4 = "A slightly longer message to test encryption.";
    char *key4 = "ThisIsALongerKey";
    char *encrypted4 = encryptMessage(message4, key4);
    if (encrypted4) {
        printf("Encrypted Message 4: %s\n", encrypted4);
        free(encrypted4); 
    }

    char *message5 = "Special characters: !@#$%^&*()_+=-`~[]\';,./{}|:\"<>?";
    char *key5 = "ComplexKey!";
    char *encrypted5 = encryptMessage(message5, key5);
    if (encrypted5) {
        printf("Encrypted Message 5: %s\n", encrypted5);
        free(encrypted5); 
    }

    return 0;
}