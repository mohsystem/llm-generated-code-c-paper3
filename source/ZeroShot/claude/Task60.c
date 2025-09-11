
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expandedForm(int num) {
    char* result = (char*)malloc(1000);  // Allocate enough space
    result[0] = '\\0';
    long multiplier = 1;
    int first = 1;
    
    while (num > 0) {
        int digit = num % 10;
        if (digit > 0) {
            char temp[100];
            if (!first) {
                strcat(result, " + ");
            }
            sprintf(temp, "%d", digit * multiplier);
            strcat(result, temp);
            first = 0;
        }
        num /= 10;
        multiplier *= 10;
    }
    
    // Reverse the string
    int len = strlen(result);
    for(int i = 0; i < len/2; i++) {
        char temp = result[i];
        result[i] = result[len-1-i];
        result[len-1-i] = temp;
    }
    
    return result;
}

int main() {
    printf("%s\\n", expandedForm(12));    // "10 + 2"
    printf("%s\\n", expandedForm(42));    // "40 + 2"
    printf("%s\\n", expandedForm(70304)); // "70000 + 300 + 4"
    printf("%s\\n", expandedForm(4982));  // "4000 + 900 + 80 + 2"
    printf("%s\\n", expandedForm(1000));  // "1000"
    return 0;
}
