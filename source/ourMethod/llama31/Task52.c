#include <stdio.h>
#include <stdlib.h>

void encryptFile(const char* inputFile, const char* outputFile, int key) {
    FILE* fin = fopen(inputFile, "r");
    FILE* fout = fopen(outputFile, "w");

    if (!fin || !fout) {
        printf("Error opening files.\n");
        return;
    }

    char c;
    while ((c = fgetc(fin)) != EOF) {
        fputc((char)(c + key), fout);
    }

    fclose(fin);
    fclose(fout);
    printf("File encrypted successfully.\n");
}

void decryptFile(const char* inputFile, const char* outputFile, int key) {
    FILE* fin = fopen(inputFile, "r");
    FILE* fout = fopen(outputFile, "w");

    if (!fin || !fout) {
        printf("Error opening files.\n");
        return;
    }

    char c;
    while ((c = fgetc(fin)) != EOF) {
        fputc((char)(c - key), fout);
    }

    fclose(fin);
    fclose(fout);
    printf("File decrypted successfully.\n");
}

int main() {
    const char* inputFile = "input.txt";
    const char* encryptedFile = "encrypted.txt";
    const char* decryptedFile = "decrypted.txt";
    int key = 3;

    encryptFile(inputFile, encryptedFile, key);
    decryptFile(encryptedFile, decryptedFile, key);

    return 0;
}