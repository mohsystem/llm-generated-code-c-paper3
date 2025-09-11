#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(const char* input, char* output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    if (j == 11 && output[0] == '1') {
        memmove(output, output + 1, j);
        output[10] = '\0';
    }
}

int main() {
    char cleaned[12];
    
    cleanPhoneNumber("+1 (613)-995-0253", cleaned);
    printf("%s\n", cleaned); // 6139950253
    
    cleanPhoneNumber("613-995-0253", cleaned);
    printf("%s\n", cleaned); // 6139950253
    
    cleanPhoneNumber("1 613 995 0253", cleaned);
    printf("%s\n", cleaned); // 6139950253
    
    cleanPhoneNumber("613.995.0253", cleaned);
    printf("%s\n", cleaned); // 6139950253
    
    cleanPhoneNumber("+1-800-555-2468", cleaned);
    printf("%s\n", cleaned); // 8005552468
    
    return 0;
}