#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *text, int s) {
    int n = strlen(text);

    for (int i = 0; i < n; i++) {
        if (isupper(text[i]))
            text[i] = (text[i] + s - 65) % 26 + 65;
        else
            text[i] = (text[i] + s - 97) % 26 + 97;
    }
}

int main() {
    char text[] = "HELLO";
    encrypt(text, 4);
    printf("%s\n", text);  // prints "LIPPS"
    return 0;
}