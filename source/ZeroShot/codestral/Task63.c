// This is a C version using OpenSSL library for Base64 decoding and Jansson library for JSON parsing.
// Install OpenSSL and Jansson libraries before running the code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <jansson.h>

char *base64_decode(const char *data, int input_length, int *output_length) {
    BIO *b64, *bmem;
    char *buffer = (char *)malloc(input_length);
    memset(buffer, 0, input_length);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new_mem_buf(data, input_length);
    bmem = BIO_push(b64, bmem);
    *output_length = BIO_read(bmem, buffer, input_length);
    BIO_free_all(bmem);

    return buffer;
}

json_t *processRequest(const char *rawData) {
    int decodedLength;
    char *decodedData = base64_decode(rawData, strlen(rawData), &decodedLength);
    json_t *json = json_loads(decodedData, 0, NULL);
    free(decodedData);
    return json;
}

int main() {
    // Test cases
    const char *test1 = "eyJuYW1lIjoiSm9obiIsImVtYWlsIjoiSm9obi5Kb2huQGVtYWlsLmNvbSJ9";
    const char *test2 = "eyJuYW1lIjoiTWFya2VyIiwiZW1haWwiOiJNYXJrZXJAZW1haWwuY29tIn0=";
    const char *test3 = "eyJuYW1lIjoiQXJpYW4iLCJlbWFpbCI6IkFyaWFuQGVtYWlsLmNvbSJ9";
    const char *test4 = "eyJuYW1lIjoiTW9yayIsImVtYWlsIjoiTW9yay5Nb3JrQGVtYWlsLmNvbSJ9";
    const char *test5 = "eyJuYW1lIjoiQ2hyaXN0YW4iLCJlbWFpbCI6IkNoaXN0YW5AZW1haWwuY29tIn0=";

    json_t *result1 = processRequest(test1);
    json_t *result2 = processRequest(test2);
    json_t *result3 = processRequest(test3);
    json_t *result4 = processRequest(test4);
    json_t *result5 = processRequest(test5);

    char *json_str1 = json_dumps(result1, JSON_INDENT(2));
    char *json_str2 = json_dumps(result2, JSON_INDENT(2));
    char *json_str3 = json_dumps(result3, JSON_INDENT(2));
    char *json_str4 = json_dumps(result4, JSON_INDENT(2));
    char *json_str5 = json_dumps(result5, JSON_INDENT(2));

    printf("%s\n", json_str1);
    printf("%s\n", json_str2);
    printf("%s\n", json_str3);
    printf("%s\n", json_str4);
    printf("%s\n", json_str5);

    json_decref(result1);
    json_decref(result2);
    json_decref(result3);
    json_decref(result4);
    json_decref(result5);
    free(json_str1);
    free(json_str2);
    free(json_str3);
    free(json_str4);
    free(json_str5);

    return 0;
}