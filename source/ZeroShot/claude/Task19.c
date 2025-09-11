
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_str(char* str, int start, int end) {
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* reverse_words(const char* input) {
    char* result = strdup(input);
    int len = strlen(result);
    int start = 0;
    
    for(int i = 0; i <= len; i++) {
        if(result[i] == ' ' || result[i] == '\\0') {
            if(i - start >= 5) {
                reverse_str(result, start, i-1);
            }
            start = i + 1;
        }
    }
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", reverse_words("Hey fellow warriors")); // "Hey wollef sroirraw"
    printf("%s\\n", reverse_words("This is a test")); // "This is a test"
    printf("%s\\n", reverse_words("This is another test")); // "This is rehtona test"
    printf("%s\\n", reverse_words("Welcome")); // "emocleW"
    printf("%s\\n", reverse_words("to the jungle")); // "to the elgnuj"
    return 0;
}
