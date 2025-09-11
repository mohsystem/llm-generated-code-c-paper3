#include <stdio.h>
#include <string.h>

void expandedForm(int num, char* result) {
    char buffer[12];
    int pow = 1;

    while (num > 0) {
        int digit = num % 10;
        num /= 10;

        if (digit != 0) {
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            sprintf(buffer, "%d", digit * pow);
            strcat(buffer, result);
            strcpy(result, buffer);
        }

        pow *= 10;
    }
}

int main() {
    char result[100];

    expandedForm(12, result);
    printf("%s\n", result);

    expandedForm(42, result);
    printf("%s\n", result);

    expandedForm(70304, result);
    printf("%s\n", result);

    return 0;
}