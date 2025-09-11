#include <stdio.h>
#include <string.h>

void expanded_form(int num, char* result) {
    int power = 1;
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0) {
            if (strlen(result) != 0) {
                strcat(result, " + ");
            }
            char digit_str[10];
            sprintf(digit_str, "%d", digit * power);
            strcat(result, digit_str);
        }
        num /= 10;
        power *= 10;
    }
}

int main() {
    char result[100] = "";
    expanded_form(12, result);
    printf("%s\n", result); // Should return "10 + 2"
    expanded_form(42, result);
    printf("%s\n", result); // Should return "40 + 2"
    expanded_form(70304, result);
    printf("%s\n", result); // Should return "70000 + 300 + 4"
    return 0;
}