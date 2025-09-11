
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PHONE_LENGTH 20

int cleanPhoneNumber(const char* input, char* output) {
    int inputLen = strlen(input);
    int outputIdx = 0;
    char cleaned[MAX_PHONE_LENGTH] = {0};
    
    // Remove all non-digit characters
    for (int i = 0; i < inputLen && outputIdx < MAX_PHONE_LENGTH - 1; i++) {
        if (isdigit(input[i])) {
            cleaned[outputIdx++] = input[i];
        }
    }
    cleaned[outputIdx] = '\\0';
    
    // Remove leading 1 if present
    if (cleaned[0] == '1' && strlen(cleaned) == 11) {
        memmove(cleaned, cleaned + 1, strlen(cleaned));
    }
    
    // Validate length and first digit
    if (strlen(cleaned) != 10) {
        return -1; // Invalid length
    }
    
    if (cleaned[0] < '2' || cleaned[0] > '9') {
        return -2; // Invalid area code
    }
    
    if (cleaned[3] < '2' || cleaned[3] > '9') {
        return -3; // Invalid exchange code
    }
    
    strcpy(output, cleaned);
    return 0;
}

int main() {
    const char* testCases[] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "223-456-7890"
    };
    
    for (int i = 0; i < 5; i++) {
        char result[MAX_PHONE_LENGTH];
        printf("Input: %s\\n", testCases[i]);
        
        int status = cleanPhoneNumber(testCases[i], result);
        if (status == 0) {
            printf("Output: %s\\n", result);
        } else if (status == -1) {
            printf("Error: Invalid phone number length\\n");
        } else if (status == -2) {
            printf("Error: Area code must start with 2-9\\n");
        } else if (status == -3) {
            printf("Error: Exchange code must start with 2-9\\n");
        }
        printf("\\n");
    }
    
    return 0;
}
