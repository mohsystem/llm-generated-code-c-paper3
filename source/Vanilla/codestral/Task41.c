#include <stdio.h>
#include <ctype.h>
#include <string.h>

void processString(char *input, char *output) {
    strcpy(output, input);
    // Add your processing logic here
    for (int i = 0; output[i]; i++)
        output[i] = toupper(output[i]);
}

int main() {
    char input[] = "Hello, World!";
    char output[100];
    processString(input, output);
    printf("%s\n", output);
    return 0;
}