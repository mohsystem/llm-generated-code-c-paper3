#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>


// Helper function to convert binary hash to hex string
char* hashToHex(unsigned char* hash, int hashLen) {
    char* hexString = (char*)malloc(sizeof(char) * (hashLen * 2 + 1));
    for (int i = 0; i < hashLen; i++) {
        sprintf(&hexString[i * 2], "%02x", (unsigned int)hash[i]);
    }
    hexString[hashLen * 2] = '\0';
    return hexString;
}


bool verifyCertificateHash(const char* certificatePath, const char* expectedHash) {
    FILE* fp = fopen(certificatePath, "r");

    if (fp == NULL) {
        perror("Error opening certificate file");
        return false;
    }

     X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);
     fclose(fp);

     if (!cert) {
         fprintf(stderr, "Error reading certificate\n");
          ERR_print_errors_fp(stderr);

         return false;
     }


    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hashLen;

    if (!X509_digest(cert, EVP_sha256(), hash, &hashLen)) {
         fprintf(stderr, "Error calculating certificate hash\n");
         X509_free(cert);
         return false;
     }

    X509_free(cert);

    char* hexHash = hashToHex(hash, hashLen);
    bool result = strcmp(hexHash, expectedHash) == 0;

    free(hexHash); // Free allocated memory


    return result;

}

int main() {
    // Test cases
    printf("%d\n", verifyCertificateHash("cert.pem", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")); // Example
    printf("%d\n", verifyCertificateHash("cert.pem", "incorrect_hash")); // Example


    return 0;
}