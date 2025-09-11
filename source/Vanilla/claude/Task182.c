
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* cleanPhoneNumber(const char* phoneNumber, char* result) {
    int j = 0;
    char cleaned[20] = {0};
    
    // Extract digits
    for(int i = 0; phoneNumber[i]; i++) {
        if(isdigit(phoneNumber[i])) {
            cleaned[j++] = phoneNumber[i];
        }
    }
    cleaned[j] = '\\0';
    
    if(strlen(cleaned) > 11 || strlen(cleaned) < 10) {
        result[0] = '\\0';
        return result;
    }
    
    if(strlen(cleaned) == 11) {
        if(cleaned[0] != '1') {
            result[0] = '\\0';
            return result;
        }
        strcpy(cleaned, cleaned + 1);
    }
    
    if(strlen(cleaned) != 10) {
        result[0] = '\\0';
        return result;
    }
    
    if(cleaned[0] < '2') {
        result[0] = '\\0';
        return result;
    }
    
    if(cleaned[3] < '2') {
        result[0] = '\\0';
        return result;
    }
    
    strcpy(result, cleaned);
    return result;
}

int main() {
    const char* tests[] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "123-456-7890"
    };
    
    char result[20];
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        cleanPhoneNumber(tests[i], result);
        printf("Output: %s\\n", result);
    }
    
    return 0;
}
