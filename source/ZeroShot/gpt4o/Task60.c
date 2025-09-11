#include <stdio.h>
#include <string.h>

void expandedForm(int num, char* result) {
    char buffer[50];
    result[0] = '\0';
    int divisor = 10;
    while (num > 0) {
        int remainder = num % divisor;
        if (remainder > 0) {
            if (strlen(result) > 0) {
                strcat(result, " + ");
            }
            snprintf(buffer, sizeof(buffer), "%d", remainder);
            strcat(result, buffer);
        }
        num -= remainder;
        divisor *= 10;
    }
}

int main() {
    char result[100];

    expandedForm(12, result);
    printf("%s\n", result);    // Should return "10 + 2"
    
    expandedForm(42, result);
    printf("%s\n", result);    // Should return "40 + 2"
    
    expandedForm(70304, result);
    printf("%s\n", result);    // Should return "70000 + 300 + 4"
    
    expandedForm(5, result);
    printf("%s\n", result);    // Should return "5"
    
    expandedForm(5600, result);
    printf("%s\n", result);    // Should return "5000 + 600"
    
    return 0;
}