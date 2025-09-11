#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <libbase64.h>

char* base64_decode(const char* base64_str, size_t* decoded_len) {
    size_t base64_len = strlen(base64_str);
    char* decoded_data = malloc(base64_len); 
    base64_decode(base64_str, base64_len, decoded_data, decoded_len, 0);
    return decoded_data;
}

json_t* process_request(const char* raw_data) {
    size_t decoded_len;
    char* decoded_data = base64_decode(raw_data, &decoded_len);
    decoded_data[decoded_len] = '\0'; 

    json_error_t error;
    json_t* deserialized_data = json_loads(decoded_data, 0, &error);
    free(decoded_data);
    
    return deserialized_data;
}

void print_json_object(json_t* json_obj) {
    const char* key;
    json_t* value;
    json_object_foreach(json_obj, key, value) {
        printf("%s: %s\n", key, json_string_value(value));
    }
}

int main() {
    const char* test_cases[] = {
        "eyJrZXkiOiAidmFsdWUifQ==",
        "eyJ0ZXN0IjogInRlc3QxIn0=",
        "eyJleGFtcGxlIjogImV4YW1wbGUifQ==",
        "eyJmb28iOiAiYmFyIn0=",
        "eyJkYXRhIjogInNhbXBsZSJ9"
    };

    for (int i = 0; i < 5; i++) {
        json_t* result = process_request(test_cases[i]);
        if (result) {
            print_json_object(result);
            json_decref(result);
        }
    }
    return 0;
}