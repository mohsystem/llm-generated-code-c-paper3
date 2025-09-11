#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <base64.h> // You need to include a base64 library
#include <json/json.h> // You need to include a JSON library
#include <tinyxml2.h> // You need to include a XML library

void processRequest(const char* raw_data) {
    if (raw_data == NULL || *raw_data == '\0') {
        printf("Invalid input\n");
        return;
    }

    try {
        // Decode the raw_data using Base64
        char* decoded_data = base64_decode(raw_data, strlen(raw_data));

        // Deserialize the decoded data into its original format
        if (*decoded_data == '<') { // XML
            tinyxml2::XMLDocument doc;
            doc.Parse(decoded_data);
            printf("XML: %s\n", decoded_data);
        } else if (*decoded_data == '{') { // JSON
            json_t* json_object = json_loads(decoded_data, 0, NULL);
            printf("JSON: %s\n", json_dumps(json_object, JSON_INDENT(4)));
            json_decref(json_object);
        } else {
            printf("Unknown format: %s\n", decoded_data);
        }

        free(decoded_data);
    } catch (const char* e) {
        printf("Error processing request: %s\n", e);
    }
}

int main() {
    // Test cases
    const char* testCases[] = {
        "SGVsbG8gd29ybGQh", // Base64 encoded "Hello world!"
        "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz48cmVxdWlyZWRfdGltZT4yMDI0LTA5LTI4PC9yZXF1aXJlZF90aW1lPjwvY2F0Pj4=", // Base64 encoded XML
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIn0.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIn0.", // Base64 encoded JSON
        "", // Empty string
        NULL // Null input
    };

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        processRequest(testCases[i]);
    }

    return 0;
}