#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>


// Simple XOR encryption for demonstration (insecure for real-world use)
void encrypt_decrypt(const unsigned char* key, unsigned char* data, int data_len) {
    for (int i = 0; i < data_len; ++i) {
        data[i] ^= key[i % AES_BLOCK_SIZE];
    }
}

void encrypt_file(const char* key, const char* input_file, const char* output_file) {
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");

    if (!in_file || !out_file) {
        fprintf(stderr, "Error opening files.\n");
        return;
    }

    unsigned char buffer[AES_BLOCK_SIZE];
    size_t bytes_read;

     unsigned char aes_key[AES_BLOCK_SIZE]; // Use a proper key derivation function in real applications.
     strncpy((char*)aes_key, key, AES_BLOCK_SIZE); // Copy the key


    while ((bytes_read = fread(buffer, 1, sizeof(buffer), in_file)) > 0) {
        encrypt_decrypt(aes_key, buffer, bytes_read);
        fwrite(buffer, 1, bytes_read, out_file);
    }

    fclose(in_file);
    fclose(out_file);
}

void decrypt_file(const char* key, const char* input_file, const char* output_file) {
     encrypt_file(key, input_file, output_file); // XOR decryption is the same as encryption.

}

int main() {
    // Example usage (replace with secure key generation/management)
    const char* key = "MySecretKey12345"; // Should be a strong, randomly generated key

    encrypt_file(key, "test1.txt", "test1.enc");
    decrypt_file(key, "test1.enc", "test1.dec");

        encrypt_file(key, "test2.txt", "test2.enc");
    decrypt_file(key, "test2.enc", "test2.dec");

        encrypt_file(key, "test3.txt", "test3.enc");
    decrypt_file(key, "test3.enc", "test3.dec");

        encrypt_file(key, "test4.txt", "test4.enc");
    decrypt_file(key, "test4.enc", "test4.dec");

        encrypt_file(key, "test5.txt", "test5.enc");
    decrypt_file(key, "test5.enc", "test5.dec");



    return 0;
}