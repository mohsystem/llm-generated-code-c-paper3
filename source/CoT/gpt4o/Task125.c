#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toLowerCase(char* str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower((unsigned char)str[i]);
    }
}

const char* accessResource(const char* userInput) {
    char input[100];
    strcpy(input, userInput);
    toLowerCase(input);
    if (strcmp(input, "resource1") == 0) {
        return "Accessing Resource 1";
    } else if (strcmp(input, "resource2") == 0) {
        return "Accessing Resource 2";
    } else if (strcmp(input, "resource3") == 0) {
        return "Accessing Resource 3";
    } else {
        return "Invalid resource";
    }
}

int main() {
    printf("%s\n", accessResource("resource1")); // Accessing Resource 1
    printf("%s\n", accessResource("resource2")); // Accessing Resource 2
    printf("%s\n", accessResource("RESOURCE3")); // Accessing Resource 3
    printf("%s\n", accessResource("resource4")); // Invalid resource
    printf("%s\n", accessResource("RESOURCE1")); // Accessing Resource 1
    return 0;
}