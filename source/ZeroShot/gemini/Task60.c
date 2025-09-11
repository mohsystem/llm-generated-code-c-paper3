#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse a string
void reverseString(char *str) {
    int len = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}


char* expandedForm(int num) {
    char* result = (char*)malloc(100 * sizeof(char)); // Allocate memory
    result[0] = '\0'; // Initialize as empty string
    int divisor = 1;
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0) {
            char part[20];
            sprintf(part, "%d", digit * divisor);
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            strcat(result, part);
        }
        num /= 10;
        divisor *= 10;
    }
    return result;
}

int main() {
    printf("%s\n", expandedForm(12)); // Output: 10 + 2
    printf("%s\n", expandedForm(42)); // Output: 40 + 2
    printf("%s\n", expandedForm(70304)); // Output: 70000 + 300 + 4
    printf("%s\n", expandedForm(800)); // Output: 800
    printf("%s\n", expandedForm(10203)); // Output: 10000 + 200 + 3
     // Free allocated memory
    free(expandedForm(12));
    free(expandedForm(42));
    free(expandedForm(70304));
    free(expandedForm(800));
    free(expandedForm(10203));

    return 0;
}