
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <jansson.h>

#define MAX_BUFFER_SIZE 4096

char* process_request(const char* raw_data) {
    if (raw_data == NULL || strlen(raw_data) == 0) {
        return NULL;
    }

    BIO *bio, *b64;
    char *decoded_data = malloc(MAX_BUFFER_SIZE);
    if (!decoded_data) {
        return NULL;
    }
    memset(decoded_data, 0, MAX_BUFFER_SIZE);

    // Create BIO for base64 decoding
    bio = BIO_new_mem_buf(raw_data, -1);
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    // Decode base64
    int decoded_size = BIO_read(bio, decoded_data, strlen(raw_data));
    BIO_free_all(bio);

    if (decoded_size <= 0) {
        free(decoded_data);
        return NULL;
    }

    // Parse JSON
    json_error_t error;
    json_t *json = json_loads(decoded_data, 0, &error);
    free(decoded_data);

    if (!json) {
        return NULL;
    }

    // Convert back to string
    char *result = json_dumps(json, JSON_COMPACT);
    json_decref(json);

    return result;
}

int main() {
    const char* test_cases[] = {
        "eyJuYW1lIjoiSm9obiIsImFnZSI6MzB9",
        "eyJpZCI6MSwidGl0bGUiOiJUZXN0In0=",
        "eyJlbWFpbCI6InRlc3RAZXhhbXBsZS5jb20ifQ==",
        "eyJhY3RpdmUiOnRydWUsInJvbGUiOiJ1c2VyIn0=",
        "eyJkYXRhIjpbMSwyLDNdfQ=="
    };

    for (int i = 0; i < 5; i++) {
        printf("Test case %d:\\n", i + 1);
        char* result = process_request(test_cases[i]);
        if (result) {
            printf("Result: %s\\n", result);
            free(result);
        } else {
            printf("Error processing request\\n");
        }
        printf("\\n");
    }

    return 0;
}
