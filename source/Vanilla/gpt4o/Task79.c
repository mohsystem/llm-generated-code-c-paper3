#include <stdio.h>
#include <string.h>

char* encryptMessage(const char* message, const char* key) {
    static char encrypted[256];
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        char c = message[i];
        char k = key[i % strlen(key)];
        encrypted[i] = c + k;
    }
    encrypted[length] = '\0';
    return encrypted;
}

int main() {
    printf("%s\n", encryptMessage("hello", "key")); // Test case 1
    printf("%s\n", encryptMessage("world", "abc")); // Test case 2
    printf("%s\n", encryptMessage("java", "123"));  // Test case 3
    printf("%s\n", encryptMessage("encryption", "secret")); // Test case 4
    printf("%s\n", encryptMessage("message", "keykey")); // Test case 5
    return 0;
}