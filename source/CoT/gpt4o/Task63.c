#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h> // Assumed JSON library
#include <openssl/bio.h>
#include <openssl/evp.h>

char *decode_base64(const char *input) {
    BIO *bio, *b64;
    char inbuf[512];
    int inlen;
    char *output = (char *)malloc(strlen(input) * 3 / 4 + 1);

    if (output == NULL) return NULL;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(input, -1);
    bio = BIO_push(b64, bio);

    inlen = BIO_read(bio, output, strlen(input));
    output[inlen] = '\0';

    BIO_free_all(bio);

    return output;
}

json_t *process_request(const char *raw_data) {
    char *decoded_data;
    json_t *json_data;
    json_error_t error;

    // Decode base64 encoded data
    decoded_data = decode_base64(raw_data);
    if (decoded_data == NULL) {
        fprintf(stderr, "Failed to decode base64\n");
        return NULL;
    }

    // Deserialize JSON
    json_data = json_loads(decoded_data, 0, &error);
    free(decoded_data);
    if (!json_data) {
        fprintf(stderr, "JSON error: %s\n", error.text);
        return NULL;
    }

    // Store deserialized data in a variable
    return json_data;
}

int main() {
    json_t *result;

    result = process_request("eyJrZXkiOiAidmFsdWUifQ==");
    if (result) {
        char *s = json_dumps(result, JSON_ENCODE_ANY);
        printf("%s\n", s); // {"key": "value"}
        free(s);
        json_decref(result);
    }

    result = process_request("eyJmb28iOiAiYmFyIn0=");
    if (result) {
        char *s = json_dumps(result, JSON_ENCODE_ANY);
        printf("%s\n", s); // {"foo": "bar"}
        free(s);
        json_decref(result);
    }

    result = process_request("eyJ4eHgiOiAieXl5In0=");
    if (result) {
        char *s = json_dumps(result, JSON_ENCODE_ANY);
        printf("%s\n", s); // {"xxx": "yyy"}
        free(s);
        json_decref(result);
    }

    result = process_request("eyJhc2QiOiAiZnJvZyJ9");
    if (result) {
        char *s = json_dumps(result, JSON_ENCODE_ANY);
        printf("%s\n", s); // {"asd": "frog"}
        free(s);
        json_decref(result);
    }

    result = process_request("eyJzdW5ueSI6ICJza3kifQ==");
    if (result) {
        char *s = json_dumps(result, JSON_ENCODE_ANY);
        printf("%s\n", s); // {"sunny": "sky"}
        free(s);
        json_decref(result);
    }

    return 0;
}