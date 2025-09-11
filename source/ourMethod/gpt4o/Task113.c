#include <stdio.h>
#include <string.h>

void concatenateStrings(const char *strings[], int count, char *result, size_t resultSize) {
    strcpy(result, "");
    for (int i = 0; i < count; i++) {
        strncat(result, strings[i], resultSize - strlen(result) - 1);
    }
}

int main() {
    char result[100];

    const char *test1[] = {"Hello", " ", "World"};
    concatenateStrings(test1, 3, result, sizeof(result));
    printf("%s\n", result);

    const char *test2[] = {"Java", " ", "Python"};
    concatenateStrings(test2, 3, result, sizeof(result));
    printf("%s\n", result);

    const char *test3[] = {"Concatenate", " ", "Strings"};
    concatenateStrings(test3, 3, result, sizeof(result));
    printf("%s\n", result);

    const char *test4[] = {"Test", " ", "Case"};
    concatenateStrings(test4, 3, result, sizeof(result));
    printf("%s\n", result);

    const char *test5[] = {"Secure", " ", "Code"};
    concatenateStrings(test5, 3, result, sizeof(result));
    printf("%s\n", result);

    return 0;
}