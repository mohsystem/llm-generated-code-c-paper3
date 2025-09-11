#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <base64.h>

char* generateSecretKey() {
    unsigned char secret[16];
    for (int i = 0; i < 16; ++i) {
        secret[i] = rand() % 256;
    }
    return base64_encode(secret, 16);
}

char* getTOTPCode(const char* secretKey) {
    unsigned char secret[16];
    base64_decode(secretKey, strlen(secretKey), secret, 16);

    time_t now = time(0);
    uint64_t counter = now / 30;

    unsigned char hmac[20];
    unsigned int hmac_len = 20;
    HMAC(EVP_sha1(), secret, 16, (const unsigned char*)&counter, 8, hmac, &hmac_len);

    uint32_t offset = hmac[19] & 0xf;
    uint32_t truncated_hmac = (hmac[offset] & 0x7f) << 24 | (hmac[offset + 1] & 0xff) << 16 | (hmac[offset + 2] & 0xff) << 8 | (hmac[offset + 3] & 0xff);
    char totp_code[7];
    sprintf(totp_code, "%06d", truncated_hmac % 1000000);
    return strdup(totp_code);
}

int verifyTOTPCode(const char* secretKey, const char* userInput) {
    char* totp_code = getTOTPCode(secretKey);
    int result = strcmp(totp_code, userInput) == 0;
    free(totp_code);
    return result;
}

int main() {
    char* secretKey = generateSecretKey();
    printf("Secret Key: %s\n", secretKey);

    char* totpCode = getTOTPCode(secretKey);
    printf("TOTP Code: %s\n", totpCode);

    // Test cases
    printf("Verification Result for correct code: %d\n", verifyTOTPCode(secretKey, totpCode));
    printf("Verification Result for incorrect code: %d\n", verifyTOTPCode(secretKey, "123456"));
    printf("Verification Result for empty code: %d\n", verifyTOTPCode(secretKey, ""));
    printf("Verification Result for null code: %d\n", verifyTOTPCode(secretKey, "")); // Null is not directly supported, using empty string instead
    printf("Verification Result for different secret key: %d\n", verifyTOTPCode("differentKey", totpCode));

    free(secretKey);
    free(totpCode);

    return 0;
}