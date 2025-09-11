#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expandedForm(int num) {
    char* strNum = (char*)malloc(20 * sizeof(char));
    sprintf(strNum, "%d", num);
    char* result = (char*)malloc(100 * sizeof(char));
    result[0] = '\0';
    int len = strlen(strNum);
    for (int i = 0; i < len; i++) {
        int digit = strNum[i] - '0';
        if (digit != 0) {
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            char temp[20];
            temp[0] = digit + '0';
            temp[1] = '\0';
            strcat(result, temp);
            for (int j = 0; j < len - i - 1; j++) {
                strcat(result, "0");
            }
        }
    }
    free(strNum);
    return result;
}

int main() {
    char* res1 = expandedForm(12);
    printf("%s\n", res1); free(res1); // Should return "10 + 2"
    char* res2 = expandedForm(42);
    printf("%s\n", res2); free(res2); // Should return "40 + 2"
    char* res3 = expandedForm(70304);
    printf("%s\n", res3); free(res3); // Should return "70000 + 300 + 4"
    return 0;
}