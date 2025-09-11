#include <stdio.h>
#include <string.h>

const char* manageKeys(const char *action, const char *arg1, const char *arg2) {
    if (strcmp(action, "generate") == 0) {
        return "Key generated";
    } else if (strcmp(action, "encrypt") == 0) {
        static char result[256];
        snprintf(result, sizeof(result), "Encrypted: %s with %s", arg1, arg2);
        return result;
    } else if (strcmp(action, "decrypt") == 0) {
        static char result[256];
        snprintf(result, sizeof(result), "Decrypted: %s with %s", arg1, arg2);
        return result;
    } else if (strcmp(action, "list") == 0) {
        return "Listing keys";
    } else if (strcmp(action, "delete") == 0) {
        static char result[256];
        snprintf(result, sizeof(result), "Deleted key: %s", arg1);
        return result;
    } else {
        return "Invalid action";
    }
}

int main() {
    printf("%s\n", manageKeys("generate", "", ""));
    printf("%s\n", manageKeys("encrypt", "hello", "key"));
    printf("%s\n", manageKeys("decrypt", "encrypted", "key"));
    printf("%s\n", manageKeys("list", "", ""));
    printf("%s\n", manageKeys("delete", "key", ""));
    return 0;
}