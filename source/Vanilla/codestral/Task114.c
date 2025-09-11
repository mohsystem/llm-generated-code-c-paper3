#include<stdio.h>
#include<string.h>
#include<ctype.h>

char *copyString(char *input) {
    char *copy = malloc(strlen(input) + 1);
    strcpy(copy, input);
    return copy;
}

char *concatenateStrings(char *str1, char *str2) {
    char *result = malloc(strlen(str1) + strlen(str2) + 2);
    strcpy(result, str1);
    strcat(result, " ");
    strcat(result, str2);
    return result;
}

char *manipulateString(char *input) {
    char *result = malloc(strlen(input) + 1);
    strncpy(result, input, 5);
    result[5] = '\0';
    for (int i = 5; i < strlen(input); i++)
        result[i] = toupper(input[i]);
    result[strlen(input)] = '\0';
    return result;
}

int main() {
    printf("%s\n", copyString("Hello"));
    printf("%s\n", concatenateStrings("Hello", "World"));
    printf("%s\n", manipulateString("HelloWorld"));
    return 0;
}