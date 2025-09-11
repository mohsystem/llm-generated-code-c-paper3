#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* copyString(const char* str) {
    static char buffer[100];
    strcpy(buffer, str);
    return buffer;
}

char* concatenateStrings(const char* str1, const char* str2) {
    static char buffer[200];
    strcpy(buffer, str1);
    strcat(buffer, str2);
    return buffer;
}

char* manipulateString(const char* str) {
    static char buffer[100];
    strcpy(buffer, str);
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = toupper(buffer[i]);
    }
    return buffer;
}

int main() {
    printf("%s\n", copyString("Hello"));
    printf("%s\n", concatenateStrings("Hello", " World"));
    printf("%s\n", manipulateString("Hello"));
    printf("%s\n", copyString("C"));
    printf("%s\n", concatenateStrings("C", " Programming"));
    return 0;
}