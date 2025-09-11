#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *str, const char *ending) {
    int len_str = strlen(str);
    int len_ending = strlen(ending);
    if (len_str >= len_ending) {
        return strcmp(str + len_str - len_ending, ending) == 0;
    }
    return false;
}

int main() {
    printf("%s\n", solution("abc", "bc") ? "true" : "false"); // true
    printf("%s\n", solution("abc", "d") ? "true" : "false");  // false
    printf("%s\n", solution("hello", "lo") ? "true" : "false");  // true
    printf("%s\n", solution("java", "a") ? "true" : "false");  // true
    printf("%s\n", solution("python", "py") ? "true" : "false");  // false
    return 0;
}