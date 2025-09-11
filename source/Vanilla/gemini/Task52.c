#include <stdio.h>
#include <stdlib.h>

const unsigned char KEY[] = {1, 2, 3, 4, 5};
const int KEY_LEN = sizeof(KEY) / sizeof(KEY[0]);

void encrypt_file(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "rb");
    FILE *outfile = fopen(output_file, "wb");

    if (!infile || !outfile) {
        perror("Error opening files");
        return;
    }

    unsigned char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), infile)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            buffer[i] ^= KEY[i % KEY_LEN];
        }
        fwrite(buffer, 1, bytes_read, outfile);
    }

    fclose(infile);
    fclose(outfile);
}

void decrypt_file(const char *input_file, const char *output_file) {
    encrypt_file(input_file, output_file); // XOR is symmetric
}


int main() {
    encrypt_file("test1.txt", "test1.enc");
    decrypt_file("test1.enc", "test1.dec");

    encrypt_file("test2.txt", "test2.enc");
    decrypt_file("test2.enc", "test2.dec");

    encrypt_file("test3.txt", "test3.enc");
    decrypt_file("test3.enc", "test3.dec");

    encrypt_file("test4.txt", "test4.enc");
    decrypt_file("test4.enc", "test4.dec");

    encrypt_file("test5.txt", "test5.enc");
    decrypt_file("test5.enc", "test5.dec");

    return 0;
}