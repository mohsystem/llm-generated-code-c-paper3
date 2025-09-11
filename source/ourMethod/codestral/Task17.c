#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_jaden_case(const char* phrase, char* result) {
    if (phrase == NULL || *phrase == '\0') {
        *result = '\0';
        return;
    }
    int i = 0;
    while (phrase[i]) {
        result[i] = phrase[i];
        if (i == 0 || phrase[i - 1] == ' ') {
            result[i] = toupper(result[i]);
        }
        i++;
    }
    result[i] = '\0';
}

int main() {
    char result[100];
    to_jaden_case("How can mirrors be real if our eyes aren't real", result);
    printf("%s\n", result);
    to_jaden_case("I'm gonna lose control like i've done before", result);
    printf("%s\n", result);
    to_jaden_case("", result);
    printf("%s\n", result);
    to_jaden_case(NULL, result);
    printf("%s\n", result);
    return 0;
}