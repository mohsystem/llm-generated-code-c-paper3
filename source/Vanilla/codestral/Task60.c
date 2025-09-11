#include <stdio.h>
#include <string.h>

void expandedForm(int num, char *result) {
    int digits[] = {10000, 1000, 100, 10, 1};
    int i = 0;
    for (int j = 0; j < 5; j++) {
        int count = num / digits[j];
        if (count > 0) {
            if (i > 0) {
                strcat(result, " + ");
            }
            char temp[10];
            sprintf(temp, "%d", count * digits[j]);
            strcat(result, temp);
            num -= count * digits[j];
            i++;
        }
    }
}

int main() {
    char result[100];
    expandedForm(12, result);
    printf("%s\n", result);  // Should return "10 + 2"
    expandedForm(42, result);
    printf("%s\n", result);  // Should return "40 + 2"
    expandedForm(70304, result);
    printf("%s\n", result);  // Should return "70000 + 300 + 4"
    return 0;
}