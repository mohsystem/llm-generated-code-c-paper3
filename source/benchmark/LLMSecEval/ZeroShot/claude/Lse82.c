#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note: C doesn't have built-in web server or JSON parsing
// This is a simplified version showing the core logic

int hexToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

void urlDecode(const char* src, char* dest) {
    int i = 0, j = 0;
    while (src[i]) {
        if (src[i] == '%' && src[i + 1] && src[i + 2]) {
            dest[j++] = hexToInt(src[i + 1]) * 16 + hexToInt(src[i + 2]);
            i += 3;
        } else if (src[i] == '+') {
            dest[j++] = ' ';
            i++;
        } else {
            dest[j++] = src[i++];
        }
    }
    dest[j] = '\0';
}

char* extractJsonValue(const char* json, const char* key, char* result) {
    char searchKey[256];
    sprintf(searchKey, "\"%s\":\"", key);

    char* pos = strstr(json, searchKey);
    if (pos != NULL) {
        pos += strlen(searchKey);
        char* endPos = strchr(pos, '"');
        if (endPos != NULL) {
            int len = endPos - pos;
            strncpy(result, pos, len);
            result[len] = '\0';
            return result;
        }
    }
    strcpy(result, "Name not found");
    return result;
}

char* processPayload(const char* payload, char* output) {
    char decoded[1024];
    char result[256];

    urlDecode(payload, decoded);
    extractJsonValue(decoded, "name", result);
    strcpy(output, result);

    return output;
}

int main() {
    char output[256];

    printf("Test Cases:\n");
    printf("1. %s\n", processPayload("%7B%22name%22%3A%22John%22%7D", output));
    printf("2. %s\n", processPayload("%7B%22name%22%3A%22Alice%22%2C%22age%22%3A30%7D", output));
    printf("3. %s\n", processPayload("%7B%22age%22%3A25%7D", output));
    printf("4. %s\n", processPayload("%7B%22name%22%3A%22Bob%20Smith%22%7D", output));
    printf("5. %s\n", processPayload("invalid", output));

    printf("Note: Full web server implementation requires external libraries\n");

    return 0;
}
