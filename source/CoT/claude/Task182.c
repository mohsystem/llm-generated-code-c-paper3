
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 50

void cleanPhoneNumber(const char* input, char* output) {
    char temp[MAX_LENGTH] = {0};
    int j = 0;
    
    // Remove all non-digit characters
    for (int i = 0; input[i] != '\\0'; i++) {
        if (isdigit(input[i])) {
            temp[j++] = input[i];
        }
    }
    temp[j] = '\\0';
    
    // Remove leading 1 if present
    if (strlen(temp) == 11 && temp[0] == '1') {
        strcpy(temp, temp + 1);
    }
    
    // Validate length and first digit
    if (strlen(temp) != 10 || temp[0] < '2') {
        strcpy(output, "Invalid phone number");
        return;
    }
    
    strcpy(output, temp);
}

int main() {
    const char* tests[] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "123-456-7890"
    };
    
    char result[MAX_LENGTH];
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        cleanPhoneNumber(tests[i], result);
        printf("Output: %s\\n\\n", result);
    }
    
    return 0;
}
