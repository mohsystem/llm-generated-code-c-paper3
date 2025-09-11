#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <base64.h>

char* base64_encode(const unsigned char* input, int length) {
    static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char* output = (char*)malloc(length * 4 / 3 + 4);
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (length--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                output[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            output[j++] = base64_chars[char_array_4[j]];

        while((i++ < 3))
            output[j++] = '=';
    }
    output[j] = '\0';
    return output;
}

char* generateToken(const char* username, const char* secretKey) {
    // Simplified token generation for demonstration purposes
    char payload[256];
    sprintf(payload, "{\"sub\":\"%s\",\"iat\":%ld,\"exp\":%ld}", username, time(NULL), time(NULL) + 120);
    unsigned char* key = (unsigned char*)secretKey;
    unsigned int keyLen = strlen(secretKey);
    unsigned char* payloadBytes = (unsigned char*)payload;
    unsigned int payloadLen = strlen(payload);
    unsigned char digest[EVP_MD_size(EVP_sha256())];
    unsigned int digestLen;

    HMAC(EVP_sha256(), key, keyLen, payloadBytes, payloadLen, digest, &digestLen);

    char* encodedPayload = base64_encode(payloadBytes, payloadLen);
    char* encodedSignature = base64_encode(digest, digestLen);

    char* token = (char*)malloc(strlen(encodedPayload) + strlen(encodedSignature) + 2);
    sprintf(token, "%s.%s", encodedPayload, encodedSignature);
    free(encodedPayload);
    free(encodedSignature);
    return token;
}

int main() {
    char* secretKey = "supersecret";
    char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    for (int i = 0; i < 5; i++) {
        char* token = generateToken(usernames[i], secretKey);
        printf("Token for %s: %s\n", usernames[i], token);
        free(token);
    }
    return 0;
}