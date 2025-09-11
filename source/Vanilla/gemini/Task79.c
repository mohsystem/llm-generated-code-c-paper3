#include <stdio.h>
#include <string.h>

char* encrypt(char* message, char* secretKey) {
    char* encryptedMessage = (char*)malloc(strlen(message) + 1);
    for (int i = 0; i < strlen(message); i++) {
        char c = message[i];
        int keyIndex = i % strlen(secretKey);
        char keyChar = secretKey[keyIndex];
        encryptedMessage[i] = (char)(c ^ keyChar);
    }
    encryptedMessage[strlen(message)] = '\0';
    return encryptedMessage;
}

int main() {
    char* encrypted1 = encrypt("hello", "key");
    printf("%s\n", encrypted1);
    free(encrypted1);

    char* encrypted2 = encrypt("world", "secret");
    printf("%s\n", encrypted2);
    free(encrypted2);
    
    char* encrypted3 = encrypt("test", "password");
    printf("%s\n", encrypted3);
    free(encrypted3);

    char* encrypted4 = encrypt("message", "cipher");
    printf("%s\n", encrypted4);
    free(encrypted4);

    char* encrypted5 = encrypt("java", "programming");
    printf("%s\n", encrypted5);
    free(encrypted5);

    return 0;
}