#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>


unsigned char key[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};


char* encrypt(const char* plaintext) {
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];

    RAND_bytes(iv, AES_BLOCK_SIZE);
    AES_set_encrypt_key(key, 128, &enc_key);

    int plaintext_len = strlen(plaintext);
    int ciphertext_len = 0;


    char *ciphertext = (char *)malloc(plaintext_len + AES_BLOCK_SIZE);

    AES_cbc_encrypt((unsigned char*)plaintext, (unsigned char*)ciphertext, plaintext_len, &enc_key, iv, AES_ENCRYPT);

    return ciphertext;
}

char* decrypt(const char* ciphertext, int ciphertext_len) {
    AES_KEY dec_key;
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);
    AES_set_decrypt_key(key, 128, &dec_key);

    char *plaintext = (char *)malloc(ciphertext_len);
    AES_cbc_encrypt((unsigned char*)ciphertext, (unsigned char*)plaintext, ciphertext_len, &dec_key, iv, AES_DECRYPT);


    plaintext[ciphertext_len - (ciphertext_len)%16] = '\0';
    return plaintext;
}



int main() {

    char* encrypted1 = encrypt("Test 1");
    int ciphertext_len1 = strlen("Test 1")+ AES_BLOCK_SIZE - (strlen("Test 1")+AES_BLOCK_SIZE)%16;
    char* decrypted1 = decrypt(encrypted1, ciphertext_len1);
    printf("Test 1: %s\n", decrypted1);
    free(encrypted1);
    free(decrypted1);




    char* encrypted2 = encrypt("Test 2");
    int ciphertext_len2 = strlen("Test 2")+ AES_BLOCK_SIZE - (strlen("Test 2")+AES_BLOCK_SIZE)%16;
    char *decrypted2 = decrypt(encrypted2, ciphertext_len2);
    printf("Test 2: %s\n", decrypted2);
    free(encrypted2);
    free(decrypted2);


    char* encrypted3 = encrypt("Test 3");
    int ciphertext_len3 = strlen("Test 3")+ AES_BLOCK_SIZE - (strlen("Test 3")+AES_BLOCK_SIZE)%16;
    char *decrypted3 = decrypt(encrypted3, ciphertext_len3);
    printf("Test 3: %s\n", decrypted3);
    free(encrypted3);
    free(decrypted3);



    char* encrypted4 = encrypt("Test 4");
    int ciphertext_len4 = strlen("Test 4")+ AES_BLOCK_SIZE - (strlen("Test 4")+AES_BLOCK_SIZE)%16;
    char* decrypted4 = decrypt(encrypted4, ciphertext_len4);
    printf("Test 4: %s\n", decrypted4);
    free(encrypted4);
    free(decrypted4);



    char* encrypted5 = encrypt("Test 5");
    int ciphertext_len5 = strlen("Test 5")+ AES_BLOCK_SIZE - (strlen("Test 5")+AES_BLOCK_SIZE)%16;
    char *decrypted5 = decrypt(encrypted5, ciphertext_len5);
    printf("Test 5: %s\n", decrypted5);
    free(encrypted5);
    free(decrypted5);

    return 0;
}