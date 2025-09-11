//  Similar to C++ implementation using OpenSSL library.  Refer to C++ code for structure.
//  Requires linking against the OpenSSL library during compilation.

#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>


// Encrypt a file
int encrypt_file(const char* input_file, const char* output_file, const unsigned char* key) {
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        return 0; // Failure
    }

    FILE *infile = fopen(input_file, "rb");
    FILE *outfile = fopen(output_file, "wb");

    if (!infile || !outfile) {
        return 0; // Failure
    }

    unsigned char input_block[AES_BLOCK_SIZE];
    unsigned char output_block[AES_BLOCK_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(input_block, 1, AES_BLOCK_SIZE, infile)) > 0) {
        if (bytes_read < AES_BLOCK_SIZE) {
            // Pad the last block with zeros
            memset(input_block + bytes_read, 0, AES_BLOCK_SIZE - bytes_read);
        }
        AES_encrypt(input_block, output_block, &aes_key);
        fwrite(output_block, 1, AES_BLOCK_SIZE, outfile);
    }

    fclose(infile);
    fclose(outfile);
    return 1; // Success
}

// Decrypt a file
int decrypt_file(const char* input_file, const char* output_file, const unsigned char* key) {
        AES_KEY aes_key;
    if (AES_set_decrypt_key(key, 128, &aes_key) < 0) {
        return 0; // Failure
    }

    FILE *infile = fopen(input_file, "rb");
    FILE *outfile = fopen(output_file, "wb");

    if (!infile || !outfile) {
        return 0; // Failure
    }


    unsigned char input_block[AES_BLOCK_SIZE];
    unsigned char output_block[AES_BLOCK_SIZE];

    while (fread(input_block, 1, AES_BLOCK_SIZE, infile) == AES_BLOCK_SIZE) {
        AES_decrypt(input_block, output_block, &aes_key);
        fwrite(output_block, 1, AES_BLOCK_SIZE, outfile);
    }

    fclose(infile);
    fclose(outfile);
    return 1; // Success
}



int main() {
    unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}; // Replace with a stronger key


    encrypt_file("test1.txt", "test1.enc", key);
    decrypt_file("test1.enc", "test1.dec", key);

    encrypt_file("test2.txt", "test2.enc", key);
    decrypt_file("test2.enc", "test2.dec", key);

    encrypt_file("test3.txt", "test3.enc", key);
    decrypt_file("test3.enc", "test3.dec", key);
    
        encrypt_file("test4.txt", "test4.enc", key);
    decrypt_file("test4.enc", "test4.dec", key);
    
        encrypt_file("test5.txt", "test5.enc", key);
    decrypt_file("test5.enc", "test5.dec", key);

    return 0;
}