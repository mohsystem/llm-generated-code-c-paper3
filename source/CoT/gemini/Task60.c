#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse a string
void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}


char* expandedForm(int num) {
    char* result = (char*)malloc(100); // Adjust size as needed
    result[0] = '\0';
    int divisor = 1;

    while (num > 0) {
        int digit = num % 10;
        if (digit > 0) {
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

    // Reverse the string (since we built it backward)
     char reversed[100]; // Assuming maximum length of 100
    strcpy(reversed, result);
    reverseString(reversed);


    char *final_result = (char*) malloc(strlen(reversed) + 1);
    strcpy(final_result, reversed);

    free(result); // Free the original result string

    return final_result;
}

int main() {
    printf("%s\n", expandedForm(12)); // Should return "10 + 2"
    printf("%s\n", expandedForm(42)); // Should return "40 + 2"
    printf("%s\n", expandedForm(70304)); // Should return "70000 + 300 + 4"
    printf("%s\n", expandedForm(800)); // Should return "800"
    printf("%s\n", expandedForm(1000000)); // Should return "1000000"

     // Free allocated memory (important to avoid memory leaks)
     free(expandedForm(12));
     free(expandedForm(42));
     free(expandedForm(70304));
     free(expandedForm(800));
     free(expandedForm(1000000));



    return 0;
}