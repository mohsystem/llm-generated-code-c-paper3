
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#define MAX_TARGET_LENGTH 100
#define MAX_DECODED_LENGTH 256

/* URL decode helper function - returns 0 on success, -1 on error */
static int url_decode(const char* encoded, char* decoded, size_t decoded_size) {
    if (!encoded || !decoded || decoded_size == 0) {
        return -1;
    }
    
    size_t enc_len = strlen(encoded);
    size_t dec_idx = 0;
    
    /* Rule#4: Ensure boundary checks during decode */
    for (size_t i = 0; i < enc_len && dec_idx < decoded_size - 1; ++i) {
        if (encoded[i] == '%' && i + 2 < enc_len) {
            /* Convert hex to char */
            char hex[3] = {encoded[i+1], encoded[i+2], '\0'};
            char* endptr = NULL;
            long value = strtol(hex, &endptr, 16);
            if (endptr == hex + 2) {
                decoded[dec_idx++] = (char)value;
                i += 2;
                continue;
            }
        } else if (encoded[i] == '+') {
            decoded[dec_idx++] = ' ';
        } else {
            decoded[dec_idx++] = encoded[i];
        }
    }
    
    /* Rule#1: Ensure null termination */
    decoded[dec_idx] = '\0';
    return 0;
}

/**
 * Validates and processes a redirect target based on secure pattern matching.
 * 
 * @param target_query_param The target query parameter value (untrusted input)
 * @param result Buffer to store result (must be at least MAX_DECODED_LENGTH bytes)
 * @return 0 on success, -1 on error
 */
int process_redirect(const char* target_query_param, char* result, size_t result_size) {
    /* Rule#1: Initialize pointers and check all inputs */
    if (!target_query_param || !result || result_size < 2) {
        if (result && result_size >= 2) {
            strncpy(result, "/", result_size - 1);
            result[result_size - 1] = '\0';
        }
        return -1;
    }

    /* Rule#3: Input validation - check for empty input */
    if (strlen(target_query_param) == 0) {
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
        return 0;
    }

    /* Allocate buffer for decoded target on stack with bounds */
    char target[MAX_DECODED_LENGTH];
    memset(target, 0, sizeof(target));

    /* Decode URL-encoded input */
    if (url_decode(target_query_param, target, sizeof(target)) != 0) {
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
        return 0;
    }

    /* Rule#3: Validate length to prevent resource exhaustion */
    size_t target_len = strlen(target);
    if (target_len > MAX_TARGET_LENGTH) {
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
        return 0;
    }

    /* Rule#3: Reject directory traversal attempts */
    if (strstr(target, "..") != NULL || target[0] == '/' || target[0] == '\\\\') {
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
        return 0;
    }

    /* Rule#3: Reject URL schemes to prevent open redirect */
    if (strstr(target, "://") != NULL ||
        (target_len >= 2 && target[0] == '/' && target[1] == '/')) {
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
        return 0;
    }

    /* Compile regex pattern - anchored to prevent partial matches */
    regex_t regex;
    int reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\\\.$", REG_EXTENDED | REG_NOSUB);
    if (reti != 0) {
        /* Regex compilation failed - fail closed */
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
        return -1;
    }

    /* Execute regex match */
    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (reti == 0) {
        /* Pattern matched - construct safe relative path */
        /* Rule#4: Bounds check before concatenation */
        if (result_size < target_len + 3) {
            strncpy(result, "/", result_size - 1);
            result[result_size - 1] = '\0';
            return 0;
        }
        snprintf(result, result_size, "./%s", target);
    } else {
        /* Pattern does not match - redirect to root */
        strncpy(result, "/", result_size - 1);
        result[result_size - 1] = '\0';
    }

    return 0;
}

int main(void) {
    char result[MAX_DECODED_LENGTH];

    /* Test case 1: Valid input matching pattern */
    const char* test1 = "test123.";
    memset(result, 0, sizeof(result));
    process_redirect(test1, result, sizeof(result));
    printf("Test 1 input: '%s' -> %s\n", test1, result);

    /* Test case 2: Valid input with hyphens */
    const char* test2 = "my-page.";
    memset(result, 0, sizeof(result));
    process_redirect(test2, result, sizeof(result));
    printf("Test 2 input: '%s' -> %s\n", test2, result);

    /* Test case 3: Invalid - missing period */
    const char* test3 = "test123";
    memset(result, 0, sizeof(result));
    process_redirect(test3, result, sizeof(result));
    printf("Test 3 input: '%s' -> %s\n", test3, result);

    /* Test case 4: Invalid - directory traversal attempt */
    const char* test4 = "../etc.";
    memset(result, 0, sizeof(result));
    process_redirect(test4, result, sizeof(result));
    printf("Test 4 input: '%s' -> %s\n", test4, result);

    /* Test case 5: Invalid - open redirect attempt */
    const char* test5 = "http://evil.com.";
    memset(result, 0, sizeof(result));
    process_redirect(test5, result, sizeof(result));
    printf("Test 5 input: '%s' -> %s\
", test5, result);

    return 0;
}
