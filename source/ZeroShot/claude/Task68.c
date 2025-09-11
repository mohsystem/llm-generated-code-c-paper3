
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ldap.h>
#include <ctype.h>

#define MAX_RESULT_SIZE 4096
#define MAX_INPUT_SIZE 256

// Function to sanitize input string
void sanitize_input(const char* input, char* output, int max_len) {
    int j = 0;
    for(int i = 0; input[i] != '\\0' && j < max_len - 1; i++) {
        if(isalnum(input[i]) || input[i] == '.' || input[i] == '-' || input[i] == '_') {
            output[j++] = input[i];
        }
    }
    output[j] = '\\0';
}

// Function to escape LDAP special characters
void escape_ldap_value(const char* input, char* output, int max_len) {
    int j = 0;
    for(int i = 0; input[i] != '\\0' && j < max_len - 4; i++) {
        switch(input[i]) {
            case '\\\\':\n                snprintf(&output[j], max_len - j, "\\\\5c");\n                j += 3;\n                break;\n            case '*':\n                snprintf(&output[j], max_len - j, "\\\\2a");\n                j += 3;\n                break;\n            case '(':\n                snprintf(&output[j], max_len - j, "\\\\28");\n                j += 3;\n                break;\n            case ')':\n                snprintf(&output[j], max_len - j, "\\\\29");\n                j += 3;\n                break;\n            default:\n                output[j++] = input[i];\n        }\n    }\n    output[j] = '\\0';\n}\n\nchar* search_ldap(const char* domain, const char* username) {\n    if(!domain || !username || !*domain || !*username) {\n        return strdup("Invalid input parameters");\n    }\n\n    char safe_domain[MAX_INPUT_SIZE];\n    char safe_username[MAX_INPUT_SIZE];\n    char escaped_username[MAX_INPUT_SIZE];\n    \n    // Sanitize inputs\n    sanitize_input(domain, safe_domain, sizeof(safe_domain));\n    sanitize_input(username, safe_username, sizeof(safe_username));\n    escape_ldap_value(safe_username, escaped_username, sizeof(escaped_username));\n\n    char* result = (char*)calloc(MAX_RESULT_SIZE, sizeof(char));\n    if(!result) {\n        return strdup("Memory allocation error");\n    }\n\n    LDAP* ld = NULL;\n    int rc;\n\n    // Initialize LDAP connection\n    ', type='text')