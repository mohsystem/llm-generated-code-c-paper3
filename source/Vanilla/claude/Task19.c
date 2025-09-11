
#include <stdio.h>
#include <string.h>

void reverseString(char* start, char* end) {
    char temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverseWords(char* str) {
    char* word_begin = str;
    char* temp = str;
    
    while (*temp) {
        temp++;
        if (*temp == '\\0') {
            if (temp - word_begin >= 5) {
                reverseString(word_begin, temp - 1);
            }
        }
        else if (*temp == ' ') {
            if (temp - word_begin >= 5) {
                reverseString(word_begin, temp - 1);
            }
            word_begin = temp + 1;
        }
    }
}

int main() {
    char tests[][100] = {
        "Hey fellow warriors",
        "This is a test",
        "This is another test",
        "Welcome",
        "Just a simple sentence"
    };
    
    for (int i = 0; i < 5; i++) {
        char test[100];
        strcpy(test, tests[i]);
        
        printf("Input: %s\\n", test);
        reverseWords(test);
        printf("Output: %s\\n\\n", test);
    }
    
    return 0;
}
