#include <stdio.h>

void encryptFile(const char* inputFile, const char* outputFile, int key) {
    FILE* fin = fopen(inputFile, "r");
    FILE* fout = fopen(outputFile, "w");

    char c;
    while ((c = fgetc(fin)) != EOF) {
        fputc(c + key, fout);
    }
    fclose(fin);
    fclose(fout);
}

void decryptFile(const char* inputFile, const char* outputFile, int key) {
    FILE* fin = fopen(inputFile, "r");
    FILE* fout = fopen(outputFile, "w");

    char c;
    while ((c = fgetc(fin)) != EOF) {
        fputc(c - key, fout);
    }
    fclose(fin);
    fclose(fout);
}

int main() {
    // Test cases
    const char* inputFile = "input.txt";
    const char* encryptedFile = "encrypted.txt";
    const char* decryptedFile = "decrypted.txt";
    int key = 3;

    encryptFile(inputFile, encryptedFile, key);
    decryptFile(encryptedFile, decryptedFile, key);
    return 0;
}