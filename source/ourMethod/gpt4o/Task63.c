#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <curl/curl.h>

char* base64_decode(const char* input, size_t* output_length) {
    CURL *curl = curl_easy_init();
    char* decoded = curl_easy_unescape(curl, input, 0, output_length);
    curl_easy_cleanup(curl);
    return decoded;
}

char* process_request(const char* raw_data) {
    size_t output_length;
    char* decoded_data = base64_decode(raw_data, &output_length);
    if (!decoded_data) {
        return NULL;
    }

    struct json_object* json_obj = json_tokener_parse(decoded_data);
    if (!json_obj) {
        free(decoded_data);
        return NULL;
    }

    const char* result = json_object_to_json_string(json_obj);
    json_object_put(json_obj);
    free(decoded_data);

    return strdup(result);
}

int main() {
    // Test cases
    printf("%s\n", process_request("eyJrZXkiOiJ2YWx1ZSJ9"));
    printf("%s\n", process_request("eyJuYW1lIjoiSm9obiJ9"));
    printf("%s\n", process_request("eyJhZ2UiOjMwfQ=="));
    printf("%s\n", process_request("eyJjaXR5IjoiTmV3IFlvcmsifQ=="));
    printf("%s\n", process_request("eyJjb3VudHJ5IjoiVVNBIn0="));

    return 0;
}