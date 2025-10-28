
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100
#define MAX_OUTPUT_LENGTH 256

bool is_alphanumeric(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != ' ') {
            return false;
        }
    }
    return true;
}

bool is_numeric(const char* str) {
    int i = 0;
    if (str[0] == '-') i = 1;
    
    if (str[i] == '\0') return false;
    
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool is_valid_email(const char* str) {
    int at_count = 0;
    int dot_after_at = 0;
    bool found_at = false;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '@') {
            at_count++;
            found_at = true;
            if (i == 0 || str[i+1] == '\0') return false;
        } else if (found_at && str[i] == '.') {
            dot_after_at++;
        }
    }
    
    return (at_count == 1 && dot_after_at > 0);
}

void validate_and_sanitize_input(const char* input, char* output) {
    if (input == NULL || strlen(input) == 0) {
        strcpy(output, "Error: Input cannot be null or empty");
        return;
    }
    
    if (strlen(input) > MAX_INPUT_LENGTH) {
        sprintf(output, "Error: Input exceeds maximum length of %d", MAX_INPUT_LENGTH);
        return;
    }
    
    int j = 0;
    for (int i = 0; input[i] != '\0' && j < MAX_OUTPUT_LENGTH - 1; i++) {
        char c = input[i];
        if (c != '<' && c != '>' && c != '"' && c != '\'' &&
            c != ';' && c != '(' && c != ')' && c != '{' &&
            c != '}' && c != '[' && c != ']' && c != '\\') {
            output[j++] = c;
        }
    }
    output[j] = '\0';

    // Trim whitespace
    while (j > 0 && isspace((unsigned char)output[j - 1])) {
        output[--j] = '\0';
    }
}

void validate_alphanumeric(const char* input, char* output) {
    char sanitized[MAX_OUTPUT_LENGTH];
    validate_and_sanitize_input(input, sanitized);

    if (strncmp(sanitized, "Error:", 6) == 0) {
        strcpy(output, sanitized);
        return;
    }

    if (!is_alphanumeric(sanitized)) {
        strcpy(output, "Error: Input must contain only alphanumeric characters and spaces");
        return;
    }

    sprintf(output, "Valid alphanumeric: %s", sanitized);
}

void validate_email(const char* input, char* output) {
    char sanitized[MAX_OUTPUT_LENGTH];
    validate_and_sanitize_input(input, sanitized);

    if (strncmp(sanitized, "Error:", 6) == 0) {
        strcpy(output, sanitized);
        return;
    }

    if (!is_valid_email(sanitized)) {
        strcpy(output, "Error: Invalid email format");
        return;
    }

    sprintf(output, "Valid email: %s", sanitized);
}

void validate_numeric(const char* input, char* output) {
    char sanitized[MAX_OUTPUT_LENGTH];
    validate_and_sanitize_input(input, sanitized);

    if (strncmp(sanitized, "Error:", 6) == 0) {
        strcpy(output, sanitized);
        return;
    }

    if (!is_numeric(sanitized)) {
        strcpy(output, "Error: Input must be a valid number");
        return;
    }

    sprintf(output, "Valid number: %s", sanitized);
}

void process_input(const char* input, const char* type, char* output) {
    if (type == NULL || strlen(type) == 0) {
        strcpy(output, "Error: Validation type not specified");
        return;
    }

    char lower_type[50];
    strcpy(lower_type, type);
    for (int i = 0; lower_type[i]; i++) {
        lower_type[i] = (char)tolower((unsigned char)lower_type[i]);
    }

    if (strcmp(lower_type, "alphanumeric") == 0) {
        validate_alphanumeric(input, output);
    } else if (strcmp(lower_type, "email") == 0) {
        validate_email(input, output);
    } else if (strcmp(lower_type, "numeric") == 0) {
        validate_numeric(input, output);
    } else {
        strcpy(output, "Error: Unknown validation type");
    }
}

int main() {
    char output[MAX_OUTPUT_LENGTH];

    printf("=== Test Case 1: Valid Alphanumeric ===\n");
    process_input("Hello World 123", "alphanumeric", output);
    printf("%s\n", output);

    printf("\n=== Test Case 2: Valid Email ===\n");
    process_input("user@example.com", "email", output);
    printf("%s\n", output);

    printf("\n=== Test Case 3: Valid Numeric ===\n");
    process_input("12345", "numeric", output);
    printf("%s\n", output);

    printf("\n=== Test Case 4: Invalid Input with Special Characters ===\n");
    process_input("<script>alert('xss')</script>", "alphanumeric", output);
    printf("%s\n", output);

    printf("\n=== Test Case 5: Input Too Long ===\n");
    char long_input[200];
    memset(long_input, 'a', 150);
    long_input[150] = '\0';
    process_input(long_input, "alphanumeric", output);
    printf("%s\n", output);

    return 0;
}

