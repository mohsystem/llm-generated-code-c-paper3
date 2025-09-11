#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char* expandedForm(int num) {
    char numStr[20]; // Adjust size as needed
    sprintf(numStr, "%d", num);
    int numLen = strlen(numStr);
    char* result = (char*)malloc(100 * sizeof(char)); // Adjust size as needed
    result[0] = '\0';

    for (int i = 0; i < numLen; i++) {
        int digit = numStr[i] - '0';
        if (digit > 0) {
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            char temp[20]; // Adjust size as needed
            sprintf(temp, "%d", (int)(digit * pow(10, numLen - i - 1)));
            strcat(result, temp);
        }
    }
    return result;
}

int main() {
    char* result1 = expandedForm(12);
    printf("%s\n", result1); // "10 + 2"
    free(result1);

    char* result2 = expandedForm(42);
    printf("%s\n", result2); // "40 + 2"
    free(result2);

    char* result3 = expandedForm(70304);
    printf("%s\n", result3); // "70000 + 300 + 4"
    free(result3);
    
    char* result4 = expandedForm(800);
    printf("%s\n", result4); // "800"
    free(result4);
    
    char* result5 = expandedForm(10000000);
    printf("%s\n", result5); // "10000000"
    free(result5);


    return 0;
}