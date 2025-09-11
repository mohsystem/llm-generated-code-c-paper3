#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to reverse a string
void reverse_string(char* str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}


char* expandedForm(int num) {
    if (num <= 0) {
        return "";  // Returning empty string for invalid input
    }

    char* result = (char*)malloc(100 * sizeof(char)); // Allocate memory for the result string
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

     // Reverse the parts
    char reversed_result[100];
    strcpy(reversed_result, result);
    char* token = strtok(reversed_result, " +");
    char* reversed_parts[10];
    int count = 0;
    while (token != NULL) {
        reversed_parts[count++] = token;
        token = strtok(NULL, " +");
    }

    strcpy(result, ""); // Clear the result string

    for (int i = count-1; i >=0; i--) {
        strcat(result, reversed_parts[i]);
        if (i > 0)
            strcat(result, " + ");
    }



    return result;
}

int main() {
    printf("%s\n", expandedForm(12)); // Should return "10 + 2"
    printf("%s\n", expandedForm(42)); // Should return "40 + 2"
    printf("%s\n", expandedForm(70304)); // Should return "70000 + 300 + 4"
    printf("%s\n", expandedForm(1000)); // Should return "1000"
    printf("%s\n", expandedForm(9000000)); // Should return "9000000"

    return 0;
}