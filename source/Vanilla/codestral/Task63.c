#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>
#include <jansson.h>

json_t* process_request(const char* raw_data) {
    size_t decoded_length;
    unsigned char* decoded_data = base64_decode(raw_data, strlen(raw_data), &decoded_length);
    char* decoded_string = (char*)malloc(decoded_length + 1);
    memcpy(decoded_string, decoded_data, decoded_length);
    decoded_string[decoded_length] = '\0';
    json_t* deserialized_data = json_loads(decoded_string, 0, NULL);
    free(decoded_data);
    free(decoded_string);
    return deserialized_data;
}

int main() {
    // Test cases
    const char* test1 = "eyJuYW1lIjoiSm9obiIsImVtYWlsIjoiam9obi5kb2VAZXhhbXBsZS5jb20ifQ==";
    json_t* result = process_request(test1);
    char* json_string = json_dumps(result, JSON_INDENT(2));
    printf("%s\n", json_string);
    json_decref(result);
    free(json_string);
    return 0;
}