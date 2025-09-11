#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>
#include <b64/cencode.h>
#include <b64/cdecode.h>


cJSON* processRequest(const char* raw_data) {
    // UTF-8 encoding is assumed for cJSON
    
    size_t input_len = strlen(raw_data);

    // Base64 Encoding
    size_t encoded_len = (input_len + 2) / 3 * 4 + 1; // Calculate encoded length
    char* encoded_data = (char*)malloc(encoded_len);
    if (!encoded_data) {
        perror("malloc failed");
        return NULL;
    }
    base64_encodestate encode_state;
    base64_init_encodestate(&encode_state);
    int encoded_size = base64_encode_block(raw_data, input_len, encoded_data, &encode_state);
    encoded_size += base64_encode_blockend(encoded_data + encoded_size, &encode_state);
    encoded_data[encoded_size] = '\0';


    // Base64 Decoding
    size_t decoded_len = encoded_size / 4 * 3 + 1; // Calculate decoded length
    char* decoded_data = (char*)malloc(decoded_len);
    if (!decoded_data) {
        perror("malloc failed");
        free(encoded_data);
        return NULL;
    }
    base64_decodestate decode_state;
    base64_init_decodestate(&decode_state);
    int decoded_size = base64_decode_block(encoded_data, encoded_size, decoded_data, &decode_state);
    decoded_data[decoded_size] = '\0';


    // Deserialize JSON
    cJSON* jsonData = cJSON_Parse(decoded_data);


    free(encoded_data);
    free(decoded_data);

    return jsonData;

}

int main() {
    const char* testCases[] = {
        "{\"name\":\"John Doe\",\"age\":30}",
        "{\"city\":\"New York\",\"country\":\"USA\"}",
        "{\"items\":[{\"id\":1},{\"id\":2}]}",
        "{\"isValid\":true}",
        "{\"message\":\"Hello, world!\"}"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        printf("Test case: %s\n", testCases[i]);
        cJSON* result = processRequest(testCases[i]);
        if (result) {
             char* result_string = cJSON_Print(result);
            printf("Result: %s\n\n", result_string);
            free(result_string);
            cJSON_Delete(result);
        } else {
            printf("Error processing request.\n\n");
        }
    }

    return 0;
}