#include <stdio.h>
#include <string.h>

char* handleInput(char* input, int bufferSize) {
    int len = strlen(input);
    if (len > bufferSize) {
        input[bufferSize] = '\0'; 
    }
    return input;
}

int main() {
    char input1[] = "Hello";
    char input2[] = "This is a long string";
    char input3[] = "";
    char input4[] = "Short";
    char input5[] = "Exactly ten chars";

    printf("%s\n", handleInput(input1, 10));
    printf("%s\n", handleInput(input2, 10));
    printf("%s\n", handleInput(input3, 5));
    printf("%s\n", handleInput(input4, 20));
    printf("%s\n", handleInput(input5, 10));

    return 0;
}