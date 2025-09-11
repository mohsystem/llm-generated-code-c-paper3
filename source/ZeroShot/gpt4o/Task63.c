#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

char *base64_decode(const char *input, int length, int *out_len) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new_mem_buf(input, length);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    char *buffer = (char *)malloc(length);
    *out_len = BIO_read(bio, buffer, length);

    BIO_free_all(bio);
    return buffer;
}

json_t *processRequest(const char *raw_data) {
    try {
        // Step 1: Ensure UTF-8 Encoding
        const char *utf8EncodedData = raw_data;

        // Step 2: Decode using Base64
        int out_len;
        char *decodedBytes = base64_decode(utf8EncodedData, strlen(utf8EncodedData), &out_len);

        // Step 3: Deserialize JSON
        json_error_t error;
        json_t *jsonData = json_loadb(decodedBytes, out_len, 0, &error);

        free(decodedBytes);

        // Step 4: Store and Return
        return jsonData;
    } catch (...) {
        // Handle exceptions securely
        return NULL;
    }
}

int main() {
    json_t *data1 = processRequest("eyJrZXkiOiAiVmFsdWUifQ=="); // {"key": "Value"}
    json_t *data2 = processRequest("eyJhZ2UiOiAzMH0="); // {"age": 30}
    json_t *data3 = processRequest("eyJjYWxsIjogIk1lIn0="); // {"call": "Me"}
    json_t *data4 = processRequest("eyJuYW1lIjogIkpvZSJ9"); // {"name": "Joe"}
    json_t *data5 = processRequest("eyJhZGRyZXNzIjogIlN0cmVldCJ9"); // {"address": "Street"}

    // Print results (assuming JSON serialization is handled)
    char *result1 = json_dumps(data1, JSON_ENCODE_ANY);
    char *result2 = json_dumps(data2, JSON_ENCODE_ANY);
    char *result3 = json_dumps(data3, JSON_ENCODE_ANY);
    char *result4 = json_dumps(data4, JSON_ENCODE_ANY);
    char *result5 = json_dumps(data5, JSON_ENCODE_ANY);

    printf("%s\n", result1);
    printf("%s\n", result2);
    printf("%s\n", result3);
    printf("%s\n", result4);
    printf("%s\n", result5);

    // Free resources
    json_decref(data1);
    json_decref(data2);
    json_decref(data3);
    json_decref(data4);
    json_decref(data5);

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}