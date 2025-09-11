
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <jansson.h>

#define MAX_BUFFER_SIZE 4096

typedef struct {
    char* data;
    size_t length;
} ProcessedData;

ProcessedData* process_request(const char* raw_data) {
    if (raw_data == NULL || strlen(raw_data) == 0) {
        return NULL;
    }

    ProcessedData* result = (ProcessedData*)malloc(sizeof(ProcessedData));
    if (!result) {
        return NULL;
    }

    // Base64 decode
    BIO *bio, *b64;
    char* decoded_data = (char*)malloc(MAX_BUFFER_SIZE);
    if (!decoded_data) {
        free(result);
        return NULL;
    }

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(raw_data, -1);
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    
    int decoded_length = BIO_read(bio, decoded_data, strlen(raw_data));
    decoded_data[decoded_length] = '\\0';

    // Parse JSON
    json_error_t error;
    json_t* json = json_loads(decoded_data, 0, &error);
    
    if (!json) {
        free(decoded_data);
        free(result);
        BIO_free_all(bio);
        return NULL;
    }

    // Convert back to string
    char* json_str = json_dumps(json, JSON_ENCODE_ANY);
    
    result->data = json_str;
    result->length = strlen(json_str);

    // Cleanup
    json_decref(json);
    free(decoded_data);
    BIO_free_all(bio);

    return result;
}

void free_processed_data(ProcessedData* data) {
    if (data) {
        free(data->data);
        free(data);
    }
}

int main() {
    const char* test_cases[] = {
        "eyJ0ZXN0IjoiSGVsbG8gV29ybGQifQ==",
        "eyJuYW1lIjoiSm9obiIsImFnZSI6MzB9",
        "eyJjb2xvciI6InJlZCIsInNpemUiOiJsYXJnZSJ9",
        "eyJpZCI6MTIzLCJhY3RpdmUiOnRydWV9",
        "eyJpdGVtcyI6WzEsMiwzXSwic3RhdHVzIjoib2sifQ=="
    };

    for (int i = 0; i < 5; i++) {
        printf("Test case %d:\\n", i + 1);
        ProcessedData* result = process_request(test_cases[i]);
        
        if (result) {
            printf("Result: %s\\n", result->data);
            free_processed_data(result);
        } else {
            printf("Error processing request\\n");
        }
        printf("\\n");
    }

    return 0;
}
