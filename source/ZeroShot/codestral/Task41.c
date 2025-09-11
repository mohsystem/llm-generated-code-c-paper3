#include<stdio.h>
#include<ctype.h>
#include<string.h>

void processString(char* input) {
    // Your processing logic here
    for(int i = 0; i < strlen(input); i++) {
        input[i] = toupper(input[i]);
    }
}

int main() {
    char str[100];
    // Test cases
    strcpy(str, "Hello, World!");
    processString(str);
    printf("%s\n", str);

    strcpy(str, "Secure Coding");
    processString(str);
    printf("%s\n", str);

    strcpy(str, "Buffer Overflow");
    processString(str);
    printf("%s\n", str);

    strcpy(str, "Vulnerabilities");
    processString(str);
    printf("%s\n", str);

    strcpy(str, "Safe Programming");
    processString(str);
    printf("%s\n", str);

    return 0;
}