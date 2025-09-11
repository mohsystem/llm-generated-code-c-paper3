#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expandedForm(int num, char* result) {
    char numStr[20];
    sprintf(numStr, "%d", num);
    char temp[20];
    int resultLen = 0;
    for (int i = 0; i < strlen(numStr); i++) {
        if (numStr[i] != '0') {
            if (resultLen > 0) {
                strcat(result, " + ");
                resultLen += 3;
            }
            temp[0] = numStr[i];
            for (int j = strlen(numStr) - 1; j > i; j--) {
                temp[j - i] = '0';
            }
            temp[j - i + 1] = '\0';
            strcat(result, temp);
            resultLen += strlen(temp);
        }
    }
}

int main() {
    char result[100];
    expandedForm(12, result);
    printf("%s\n", result); // Should return "10 + 2"
    strcpy(result, "");
    expandedForm(42, result);
    printf("%s\n", result); // Should return "40 + 2"
    strcpy(result, "");
    expandedForm(70304, result);
    printf("%s\n", result); // Should return "70000 + 300 + 4"
    strcpy(result, "");
    expandedForm(10203, result);
    printf("%s\n", result); // Test case
    strcpy(result, "");
    expandedForm(12345, result);
    printf("%s\n", result); // Test case
    return 0;
}