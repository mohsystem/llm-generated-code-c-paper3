#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

bool validate_input(const char* input, const char* pattern) {
    regex_t regex;
    int ret;
    bool result = false;
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) return false;

    ret = regexec(&regex, input, 0, NULL, 0);
    if (!ret) result = true;
    
    regfree(&regex);
    return result;
}

int main() {
    printf("%d\n", validate_input("hello123", "\\w+")); // true
    printf("%d\n", validate_input("12345", "\\d+")); // true
    printf("%d\n", validate_input("hello@", "\\w+")); // false
    printf("%d\n", validate_input("email@example.com", "^[\\w._%+-]+@[\\w.-]+\\.\\w{2,6}$")); // true
    printf("%d\n", validate_input("123abc", "\\d+")); // false
    
    return 0;
}