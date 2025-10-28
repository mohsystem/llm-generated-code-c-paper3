// Note: C doesn't have decorators or web frameworks
// This provides the core ping functionality with security measures
// Compile: gcc -o Lse111 Lse111.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_URL_LENGTH 255
#define MAX_OUTPUT_LENGTH 4096

int validate_domain(const char* url) {
    regex_t regex;
    int ret;

    const char* pattern = "^([a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,}$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) return 0;

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}

int validate_ip(const char* url) {
    regex_t regex;
    int ret;

    const char* pattern =
        "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) return 0;

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}

char* ping(const char* url) {
    static char output[MAX_OUTPUT_LENGTH];
    char command[512];
    FILE* fp;
    size_t len;

    // Validate input
    if (url == NULL || strlen(url) == 0 || strlen(url) > MAX_URL_LENGTH) {
        snprintf(output, MAX_OUTPUT_LENGTH,
                 "Invalid input: URL parameter is required and must be less than 255 characters");
        return output;
    }

    // Create sanitized copy
    char sanitized_url[MAX_URL_LENGTH + 1];
    strncpy(sanitized_url, url, MAX_URL_LENGTH);
    sanitized_url[MAX_URL_LENGTH] = '\0';

    // Remove whitespace
    len = 0;
    for (size_t i = 0; sanitized_url[i]; i++) {
        if (!isspace((unsigned char)sanitized_url[i])) {
            sanitized_url[len++] = sanitized_url[i];
        }
    }
    sanitized_url[len] = '\0';

    // Validate format
    if (!validate_domain(sanitized_url) && !validate_ip(sanitized_url)) {
        snprintf(output, MAX_OUTPUT_LENGTH,
                 "Invalid input: Must be a valid domain or IP address");
        return output;
    }

    // Build command
#ifdef _WIN32
    snprintf(command, sizeof(command), "ping -n 4 %s", sanitized_url);
#else
    snprintf(command, sizeof(command), "ping -c 4 %s", sanitized_url);
#endif

    // Execute command
    fp = popen(command, "r");
    if (fp == NULL) {
        snprintf(output, MAX_OUTPUT_LENGTH, "Error: Failed to execute ping command");
        return output;
    }

    // Read output
    size_t pos = 0;
    while (fgets(output + pos, MAX_OUTPUT_LENGTH - pos, fp) != NULL) {
        pos = strlen(output);
        if (pos >= MAX_OUTPUT_LENGTH - 1) break;
    }

    pclose(fp);
    return output;
}

int main() {
    printf("Test 1 - Valid domain:\n%s\n\n", ping("google.com"));
    printf("Test 2 - Valid IP:\n%s\n\n", ping("8.8.8.8"));
    printf("Test 3 - Invalid input:\n%s\n\n", ping("google.com; ls -la"));
    printf("Test 4 - Empty input:\n%s\n\n", ping(""));
    printf("Test 5 - Invalid format:\n%s\n\n", ping("not_a_valid_domain!"));

    return 0;
}
