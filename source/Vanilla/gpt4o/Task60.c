#include <stdio.h>
#include <string.h>

void expandedForm(int num, char *result) {
    char buffer[50] = "";
    int divisor = 10;
    int positionValue = 1;

    while (num > 0) {
        int remainder = num % divisor;
        if (remainder != 0) {
            char temp[50];
            sprintf(temp, " + %d", remainder * positionValue);
            strcat(buffer, temp);
        }
        num /= 10;
        positionValue *= 10;
    }
    strcpy(result, buffer + 3);
}

int main() {
    char result[100];

    expandedForm(12, result);
    printf("%s\n", result);    // "10 + 2"
    expandedForm(42, result);
    printf("%s\n", result);    // "40 + 2"
    expandedForm(70304, result);
    printf("%s\n", result);    // "70000 + 300 + 4"
    expandedForm(530, result);
    printf("%s\n", result);    // "500 + 30"
    expandedForm(8050, result);
    printf("%s\n", result);    // "8000 + 50"

    return 0;
}