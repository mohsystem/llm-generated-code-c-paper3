
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expandedForm(int num) {
    char* result = (char*)malloc(1000);
    result[0] = '\\0';
    long long multiplier = 1;
    
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0) {
            char temp[100];
            if (strlen(result) > 0) {
                sprintf(temp, " + %lld%s", digit * multiplier, result);
            } else {
                sprintf(temp, "%lld", digit * multiplier);
            }
            strcpy(result, temp);
        }
        num /= 10;
        multiplier *= 10;
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
