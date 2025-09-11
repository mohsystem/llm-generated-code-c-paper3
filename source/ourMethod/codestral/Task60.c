#include<stdio.h>
#include<string.h>

char* expanded_form(int num) {
    static char result[100] = "";
    for (int i = 10; i <= num; i *= 10) {
        int rem = num % i;
        num -= rem;
        if (rem > 0) {
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            char str[10];
            sprintf(str, "%d", rem);
            strcat(str, result);
            strcpy(result, str);
        }
    }
    return result;
}

int main() {
    printf("%s\n", expanded_form(12));  // Should return "10 + 2"
    printf("%s\n", expanded_form(42));  // Should return "40 + 2"
    printf("%s\n", expanded_form(70304));  // Should return "70000 + 300 + 4"
    return 0;
}