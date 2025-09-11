#include <stdio.h>
#include <string.h>

char* encryptString(const char* input, char* encrypted) {
    int i = 0;
    while (input[i] != '\0') {
        encrypted[i] = input[i] + 3;
        i++;
    }
    encrypted[i] = '\0';
    return encrypted;
}

int main() {
    char encrypted[100];
    printf("%s\n", encryptString("hello", encrypted)); // khoor
    printf("%s\n", encryptString("java", encrypted)); // mdyd
    printf("%s\n", encryptString("encryption", encrypted)); // hqfubswlrq
    printf("%s\n", encryptString("world", encrypted)); // zruog
    printf("%s\n", encryptString("testcase", encrypted)); // whvwcdrh
    return 0;
}