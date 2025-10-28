
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 256
#define MAX_RESULT_SIZE 1024

typedef struct {
    char key[128];
    char value[512];
} KeyValue;

typedef struct {
    KeyValue items[20];
    int count;
} UserInfo;

void sanitizeLdapInput(const char* input, char* output, size_t outputSize) {
    size_t j = 0;
    for (size_t i = 0; input[i] != '\0' && j < outputSize - 3; i++) {
        switch (input[i]) {
            case '\\\\':                if (j + 3 < outputSize) {                    strcpy(output + j, "\\\\5c");
                j += 3;                }                break;            case '*':                if (j + 3 < outputSize) {
                    strcpy(output + j, "\\\\2a");                    j += 3;
                }                break;            case '(':                if (j + 3 < outputSize) {
                    strcpy(output + j, "\\\\28");                    j += 3;
                }                break;            case ')':                if (j + 3 < outputSize) {
                    strcpy(output + j, "\\\\29");                    j += 3;
                }                break;            case '\0':                if (j + 3 < outputSize) {
                    strcpy(output + j, "\\\\00");                    j += 3;
                }                break;            default:                output[j++] = input[i];
        }    }    output[j] = '\0';} void sanitizeDN(const char* input, char* output, size_t outputSize) {
    size_t j = 0;    size_t len = strlen(input);        for (size_t i = 0; input[i] != '\0' && j < outputSize - 2; i++) {
        char c = input[i];        int needsEscape = 0;                if (c == '\\\\' || c == ',' || c == '+' || c == '"' ||
            c == '<' || c == '>' || c == ';' || c == '=') {            needsEscape = 1;        } else if (c == '#' && i == 0) {
                needsEscape = 1;
            } else if (c == ' ' && (i == 0 || i == len - 1)) {            needsEscape = 1;        }                if (needsEscape && j + 1 < outputSize) {            output[j++] = '\\\\';        }        output[j++] = c;
    }    output[j] = '\0';
}
void trim(char* str) {    char* start = str;    char* end;        while (isspace((unsigned char)*start)) start++;
    if (*start == 0) {        str[0] = '\0';        return;    }        end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;        *(end + 1) = '\0';
    memmove(str, start, strlen(start) + 1);}
int isValidDC(const char* dc) {
    for (size_t i = 0; dc[i] != '\0'; i++) {
        char c = dc[i];        if (!isalnum(c) && c != '-' && c != '\\\\' && c != ',') {            return 0;        }
    }    return 1;
}
void addUserInfo(UserInfo* info, const char* key, const char* value) {    if (info->count < 20) {
    strncpy(info->items[info->count].key, key, 127);        info->items[info->count].key[127] = '\0';
    strncpy(info->items[info->count].value, value, 511);        info->items[info->count].value[511] = '\0';
    info->count++;
}}
UserInfo searchUser(const char* username, const char* dc) {    UserInfo userInfo = {0};
    char trimmedUsername[MAX_INPUT_SIZE];    char trimmedDC[MAX_INPUT_SIZE];
    char sanitizedUsername[MAX_INPUT_SIZE];    char sanitizedDC[MAX_INPUT_SIZE];
    // Copy and trim inputs
    strncpy(trimmedUsername, username, MAX_INPUT_SIZE - 1);    trimmedUsername[MAX_INPUT_SIZE - 1] = '\0';    trim(trimmedUsername);
    strncpy(trimmedDC, dc, MAX_INPUT_SIZE - 1);    trimmedDC[MAX_INPUT_SIZE - 1] = '\0';    trim(trimmedDC);
     // Validate inputs
    if (strlen(trimmedUsername) == 0) {
     addUserInfo(&userInfo, "error", "Username cannot be empty");
     return userInfo;    }        if (strlen(trimmedDC) == 0) {
     addUserInfo(&userInfo, "error", "Domain component cannot be empty");        return userInfo;    }
     // Sanitize inputs
    sanitizeLdapInput(trimmedUsername, sanitizedUsername, MAX_INPUT_SIZE);
    sanitizeDN(trimmedDC, sanitizedDC, MAX_INPUT_SIZE);
    // Validate DC format
    if (!isValidDC(sanitizedDC)) {
        addUserInfo(&userInfo, "error", "Invalid domain component format");
        return userInfo;
    }        /* Note: This is a demonstration of the logic flow     * In production, you would use OpenLDAP C API here
    *      * LDAP* ld;     * ldap_initialize(&ld, "ldap://localhost:389");     * ... perform LDAP operations ...     * ldap_unbind_ext_s(ld, NULL, NULL);     */
    // Demonstration output without actual LDAP connection
    addUserInfo(&userInfo, "note", "This is a demonstration. Requires OpenLDAP library for actual LDAP operations.");
    addUserInfo(&userInfo, "sanitized_username", sanitizedUsername);    addUserInfo(&userInfo, "sanitized_dc", sanitizedDC);
    char searchFilter[MAX_RESULT_SIZE];    snprintf(searchFilter, MAX_RESULT_SIZE, "(uid=%s)", sanitizedUsername);
    addUserInfo(&userInfo, "search_filter", searchFilter);        return userInfo;}
void printResult(const UserInfo* info) {    printf("Result:");
    for (int i = 0; i < info->count; i++) {        printf("  %s: %s\\", info->items[i].key, info->items[i].value);    }}
int main(int argc, char* argv[]) {    printf("=== LDAP User Search Program ===\\");
    // Test cases
    const char* testCases[][2] = {        {"jdoe", "example,com"},        {"alice", "test,org"},
        {"bob123", "company,local"},        {"user*", "example,com"},
        // Test injection attempt
        {"admin", "corp,internal"}    };    int numTestCases = 5;
    if (argc >= 3) {
        // Use command line arguments
        printf("Searching for user: %s in domain: %s", argv[1], argv[2]);
        UserInfo result = searchUser(argv[1], argv[2]);
        printResult(&result);    } else {
            // Run test cases
            printf("No command line arguments provided. Running test cases...\\");
            for (int i = 0; i < numTestCases; i++) {
                printf("Test Case %d:\\", i + 1);
                printf("Username: %s\\", testCases[i][0]);
                printf("DC: %s\\", testCases[i][1]);
                UserInfo result = searchUser(testCases[i][0], testCases[i][1]);
                printResult(&result);            printf("-----------------------------------\\");
        }
    }
    
    return 0;
}
