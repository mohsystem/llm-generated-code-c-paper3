
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PHONE_LENGTH 20

void cleanPhoneNumber(const char* input, char* output) {
    if (!input || !output) {
        output[0] = '\\0';
        return;
    }
    
    int j = 0;
    char temp[MAX_PHONE_LENGTH] = {0};
    
    // Remove all non-digit characters
    for (int i = 0; input[i] && j < MAX_PHONE_LENGTH - 1; i++) {
        if (isdigit(input[i])) {
            temp[j++] = input[i];
        }
    }
    temp[j] = '\\0';
    
    // Remove country code 1 if present
    char* cleaned = temp;
    if (strlen(temp) > 10 && temp[0] == '1') {
        cleaned = temp + 1;
    }
    
    // Validate length and first digit
    if (strlen(cleaned) != 10 || cleaned[0] < '2' || cleaned[0] > '9') {
        output[0] = '\\0';
        return;
    }
    
    strcpy(output, cleaned);
}

int main() {
    const char* tests[] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "123-456-7890"
    };
    
    char output[MAX_PHONE_LENGTH];
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        cleanPhoneNumber(tests[i], output);
        printf("Output: %s\\n\\n", output);
    }
    
    return 0;
}
