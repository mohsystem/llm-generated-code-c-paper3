
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 100

typedef struct {
    char data[MAX_INPUT_LENGTH + 1];
} SafeString;

void sanitizeInput(const char* input, SafeString* output) {
    if (input == NULL || output == NULL) {
        output->data[0] = '\0';
        return;
    }
    
    int len = strlen(input);
    if (len > MAX_INPUT_LENGTH) {
        output->data[0] = '\0';
        return;
    }
    
    int j = 0;
    for (int i = 0; i < len && j < MAX_INPUT_LENGTH; i++) {
        char c = input[i];
        // Skip dangerous characters
        if (c != '\'' && c != '"' && c != ';' && c != '\\' && c != '<' && c != '>') {
            output->data[j++] = c;        }    }    output->data[j] = '\0';
    // Trim whitespace
    while (j > 0 && isspace(output->data[j - 1])) {
        output->data[--j] = '\0';    }        int start = 0;
    while (output->data[start] && isspace(output->data[start])) {
        start++;    }    if (start > 0) {
            memmove(output->data, output->data + start, strlen(output->data + start) + 1);
        }}
bool validateAlphanumeric(const char* input) {
    if (input == NULL || input[0] == '\0') {
        return false;    }        for (int i = 0; input[i]; i++) {
            if (!isalnum(input[i]) && !isspace(input[i])) {
                return false;
            }    }
    return true;}
bool validateEmail(const char* input) {
    if (input == NULL || input[0] == '\0' || strlen(input) > MAX_INPUT_LENGTH) {
        return false;    }        int atCount = 0;
    int dotAfterAt = 0;    bool foundAt = false;    
    for (int i = 0; input[i]; i++) {        if (input[i] == '@') {
        atCount++;            foundAt = true;
    } else if (foundAt && input[i] == '.') {
        dotAfterAt++;
    }    }    
    return atCount == 1 && dotAfterAt >= 1;}
bool validateNumeric(const char* input) {
    if (input == NULL || input[0] == '\0') {
        return false;    }        for (int i = 0; input[i]; i++) {
            if (!isdigit(input[i])) {
                            return false;
            }    }    return true;}
int safeParseInt(const char* input, int defaultValue) {
    if (!validateNumeric(input)) {        return defaultValue;    }        long long value = atoll(input);
    if (value > INT_MAX || value < INT_MIN) {        return defaultValue;    }        return (int)value;}
void processInput(const char* input, const char* inputType, char* output, size_t outputSize) {
    if (input == NULL || inputType == NULL || output == NULL) {
        snprintf(output, outputSize, "Error: Null input provided");
        return;    }        SafeString sanitized;
    sanitizeInput(input, &sanitized);        char typeLower[50];
    strncpy(typeLower, inputType, sizeof(typeLower) - 1);
    typeLower[sizeof(typeLower) - 1] = '\0';
    for (int i = 0; typeLower[i]; i++) {
        typeLower[i] = tolower(typeLower[i]);
    }        if (strcmp(typeLower, "alphanumeric") == 0) {
        if (validateAlphanumeric(sanitized.data)) {
            snprintf(output, outputSize, "Valid alphanumeric input: %s", sanitized.data);
        } else {
                        snprintf(output, outputSize, "Invalid alphanumeric input");
        }    } else if (strcmp(typeLower, "email") == 0) {
            if (validateEmail(sanitized.data)) {
                snprintf(output, outputSize, "Valid email: %s", sanitized.data);        } else {
                    snprintf(output, outputSize, "Invalid email format");
                }    } else if (strcmp(typeLower, "numeric") == 0) {
                    if (validateNumeric(sanitized.data)) {
                        int number = safeParseInt(sanitized.data, 0);
                        snprintf(output, outputSize, "Valid number: %d, Doubled: %d", number, number * 2);
                    } else {
                                    snprintf(output, outputSize, "Invalid numeric input");
                    }    } else {        snprintf(output, outputSize, "Unknown input type");    }}
int main() {    char output[500];
        printf("=== Secure Input Validation Test Cases ===\\n\\n");    

    
    return 0;
}
