#include <stdio.h>
#include <string.h>

void copyString(const char *source, char *destination, size_t size) {
    if (source == NULL || destination == NULL) return;
    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

void concatenateStrings(const char *str1, const char *str2, char *destination, size_t size) {
    if (destination == NULL) return;
    destination[0] = '\0';
    if (str1 != NULL) {
        strncat(destination, str1, size - 1);
    }
    if (str2 != NULL) {
        strncat(destination, str2, size - strlen(destination) - 1);
    }
}

void reverseString(const char *source, char *destination, size_t size) {
    if (source == NULL || destination == NULL) return;
    size_t len = strlen(source);
    if (len >= size) len = size - 1;
    for (size_t i = 0; i < len; i++) {
        destination[i] = source[len - 1 - i];
    }
    destination[len] = '\0';
}

int main() {
    char buffer[100];

    copyString("hello", buffer, sizeof(buffer));
    printf("Copy: %s\n", buffer); // hello

    concatenateStrings("hello", " world", buffer, sizeof(buffer));
    printf("Concat: %s\n", buffer); // hello world

    reverseString("hello", buffer, sizeof(buffer));
    printf("Reverse: %s\n", buffer); // olleh

    copyString(NULL, buffer, sizeof(buffer));
    printf("Copy Null: %s\n", buffer); // (empty string)

    concatenateStrings(NULL, NULL, buffer, sizeof(buffer));
    printf("Concat Nulls: %s\n", buffer); // (empty string)

    return 0;
}