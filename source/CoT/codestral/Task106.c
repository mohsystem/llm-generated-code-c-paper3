// C does not have built-in RSA encryption support, so this example uses OpenSSL library.
// You need to install OpenSSL library and link it to your project.
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>
#include <base64.h>

char* encrypt(RSA* rsa, const char* message) {
    int len = RSA_size(rsa);
    char* encrypted = malloc(len);
    int result = RSA_public_encrypt(strlen(message), (const unsigned char*)message, (unsigned char*)encrypted, rsa, RSA_PKCS1_OAEP_PADDING);
    if (result == -1) {
        ERR_print_errors_fp(stderr);
        free(encrypted);
        return NULL;
    }
    char* encrypted_message = base64_encode((unsigned char*)encrypted, len);
    free(encrypted);
    return encrypted_message;
}

char* decrypt(RSA* rsa, const char* encrypted_message) {
    int len = RSA_size(rsa);
    unsigned char* decrypted = malloc(len);
    char* decoded_message = base64_decode(encrypted_message);
    int result = RSA_private_decrypt(strlen(decoded_message), (const unsigned char*)decoded_message, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);
    if (result == -1) {
        ERR_print_errors_fp(stderr);
        free(decoded_message);
        free(decrypted);
        return NULL;
    }
    char* message = malloc(result + 1);
    strncpy(message, (char*)decrypted, result);
    message[result] = '\0';
    free(decoded_message);
    free(decrypted);
    return message;
}

int main() {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, e, NULL);

    const char* messages[] = {"Hello, World!", "Test message 2", "This is a test", "Secure RSA encryption", "Goodbye!"};
    for (int i = 0; i < 5; i++) {
        char* encrypted = encrypt(rsa, messages[i]);
        char* decrypted = decrypt(rsa, encrypted);
        printf("Original: %s\n", messages[i]);
        printf("Encrypted: %s\n", encrypted);
        printf("Decrypted: %s\n", decrypted);
        printf("\n");
        free(encrypted);
        free(decrypted);
    }

    RSA_free(rsa);
    BN_free(e);
    return 0;
}