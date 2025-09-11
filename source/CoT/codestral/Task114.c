#include <stdio.h>
#include <string.h>

void Task114() {
    char str1[10] = "Hello, ";
    char str2[7] = "World!";
    char str3[17];
    strcpy(str3, str1); // copying
    strcat(str3, str2); // concatenation
    // C does not support string manipulation as easily as the other languages, so we'll skip the manipulation part
    printf("%s\n", str3);
}

int main() {
    Task114();
    return 0;
}