#include <stdio.h>
#include <string.h>

void expandedForm(int num, char *result) {
    char buffer[50];
    result[0] = '\0';
    int placeValue = 1;
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0) {
            sprintf(buffer, "%d", digit * placeValue);
            if (strlen(result) > 0) {
                char temp[50];
                strcpy(temp, result);
                sprintf(result, "%s + %s", buffer, temp);
            } else {
                strcpy(result, buffer);
            }
        }
        num /= 10;
        placeValue *= 10;
    }
}

int main() {
    char result[100];
    expandedForm(12, result);
    printf("%s\n", result);    // Should return "10 + 2"
    expandedForm(42, result);
    printf("%s\n", result);    // Should return "40 + 2"
    expandedForm(70304, result);
    printf("%s\n", result);    // Should return "70000 + 300 + 4"
    expandedForm(5, result);
    printf("%s\n", result);    // Should return "5"
    expandedForm(1009, result);
    printf("%s\n", result);    // Should return "1000 + 9"
    return 0;
}