#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *str, const char *ending) {
    int len_str = strlen(str);
    int len_ending = strlen(ending);

    if (len_ending > len_str) {
        return false;
    }
    return strcmp(str + len_str - len_ending, ending) == 0;
}

int main() {
    printf("%s\n", solution("abc", "bc") ? "true" : "false"); // true
    printf("%s\n", solution("abc", "d") ? "true" : "false"); // false
    printf("%s\n", solution("abcde", "cde") ? "true" : "false"); // true
    printf("%s\n", solution("abc", "abc") ? "true" : "false"); // true
    printf("%s\n", solution("abc", "") ? "true" : "false"); // true
    return 0;
}