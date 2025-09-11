#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expandedForm(int num) {
    char* numStr = malloc(20 * sizeof(char));
    sprintf(numStr, "%d", num);
    char* result = malloc(100 * sizeof(char));
    result[0] = '\0';

    for (int i = 0; i < strlen(numStr); i++) {
        int digit = numStr[i] - '0';
        if (digit != 0) {
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            char temp[20];
            temp[0] = digit + '0';
            temp[1] = '\0';
            strcat(result, temp);
            for (int j = strlen(numStr) - 1 - i; j > 0; j--) {
                strcat(result, "0");
            }
        }
    }

    free(numStr);
    return result;
}

int main() {
    char* res1 = expandedForm(12);
    printf("%s\n", res1); free(res1); // Output: "10 + 2"
    char* res2 = expandedForm(42);
    printf("%s\n", res2); free(res2); // Output: "40 + 2"
    char* res3 = expandedForm(70304);
    printf("%s\n", res3); free(res3); // Output: "70000 + 300 + 4"
    char* res4 = expandedForm(100);
    printf("%s\n", res4); free(res4); // Output: "100"
    char* res5 = expandedForm(12345);
    printf("%s\n", res5); free(res5); // Output: "10000 + 2000 + 300 + 40 + 5"
    return 0;
}