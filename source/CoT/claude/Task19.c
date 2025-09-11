
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char* str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* reverseWords(const char* input) {
    if (input == NULL) return NULL;
    
    int len = strlen(input);
    char* result = (char*)malloc(len + 1);
    strcpy(result, input);
    
    char* word_start = result;
    int i;
    
    for (i = 0; i <= len; i++) {
        if (result[i] == ' ' || result[i] == '\\0') {
            int word_len = &result[i] - word_start;
            if (word_len >= 5) {
                reverseString(word_start, 0, word_len - 1);
            }
            word_start = &result[i + 1];
        }
    }
    
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", reverseWords("Hey fellow warriors"));    // "Hey wollef sroirraw"
    printf("%s\\n", reverseWords("This is a test"));        // "This is a test"
    printf("%s\\n", reverseWords("This is another test"));  // "This is rehtona test"
    printf("%s\\n", reverseWords("Reverse"));               // "esreveR"
    printf("%s\\n", reverseWords(""));                      // ""
    
    return 0;
}
