#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/sha.h>

char* loadCertificate(const char* certificatePath) {
    FILE* file = fopen(certificatePath, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open certificate file\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* certificate = (char*) malloc(fileSize + 1);
    if (!certificate) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(certificate, 1, fileSize, file);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Failed to read certificate file\n");
        exit(EXIT_FAILURE);
    }

    certificate[bytesRead] = '\0';
    fclose(file);
    return certificate;
}

char* calculateHash(const char* certificate) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, certificate, strlen(certificate));
    SHA256_Final(hash, &sha256);

    char* hashString = (char*) malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (!hashString) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashString + i * 2, "%02x", hash[i]);
    }
    hashString[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hashString;
}

int main() {
    const char* certificatePath = "path/to/your/certificate.crt";
    const char* knownHash = "known_hash_value";

    char* certificate = loadCertificate(certificatePath);
    char* calculatedHash = calculateHash(certificate);

    if (strcmp(calculatedHash, knownHash) == 0) {
        printf("The SSL certificate matches the known hash.\n");
    } else {
        printf("The SSL certificate does not match the known hash.\n");
    }

    free(certificate);
    free(calculatedHash);

    return 0;
}