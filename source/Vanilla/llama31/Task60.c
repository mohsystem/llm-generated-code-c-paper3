#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expandedForm(int num) {
    char* numStr = malloc(20 * sizeof(char));
    sprintf(numStr, "%d", num);
    int len = strlen(numStr);
    char* result = malloc(100 * sizeof(char));
    result[0] = '\0';

    for (int i = 0; i < len; i++) {
        int digit = numStr[i] - '0';
        if (digit != 0) {
            char temp[20];
            sprintf(temp, "%d", digit * (int)pow(10, len - 1 - i));
            if (strlen(result) > 0) strcat(result, " + ");
            strcat(result, temp);
        }
    }
    free(numStr);
    return result;
}

int main() {
    char* res1 = expandedForm(12);
    printf("%s\n", res1); free(res1); // Should return "10 + 2"
    char* res2 = expandedForm(42);
    printf("%s\n", res2); free(res2); // Should return "40 + 2"
    char* res3 = expandedForm(70304);
    printf("%s\n", res3); free(res3); // Should return "70000 + 300 + 4"
    char* res4 = expandedForm(100);
    printf("%s\n", res4); free(res4); // Should return "100"
    char* res5 = expandedForm(12345);
    printf("%s\n", res5); free(res5); // Should return "10000 + 2000 + 300 + 40 + 5"
    return 0;
}