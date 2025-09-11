
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void reverse_word(char* start, char* end) {
    char temp;
    while(start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char* spin_words(const char* sentence) {
    if(!sentence || strlen(sentence) == 0) {
        char* result = (char*)malloc(1);
        if(!result) return NULL;
        result[0] = '\\0';
        return result;
    }
    
    char* result = (char*)malloc(strlen(sentence) + 1);
    if(!result) return NULL;
    strcpy(result, sentence);
    
    char* word_start = result;
    char* current = result;
    
    while(*current) {
        if(*current == ' ' || *(current + 1) == '\\0') {
            char* word_end;
            if(*current == ' ') {
                word_end = current - 1;
            } else {
                word_end = current;
            }
            
            size_t word_len = word_end - word_start + 1;
            if(word_len >= 5) {
                reverse_word(word_start, word_end);
            }
            
            if(*current == ' ') {
                word_start = current + 1;
            }
        }
        current++;
    }
    
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = spin_words("Hey fellow warriors");
    printf("%s\\n", result); // Hey wollef sroirraw
    free(result);
    
    result = spin_words("This is a test");
    printf("%s\\n", result); // This is a test
    free(result);
    
    result = spin_words("This is another test");
    printf("%s\\n", result); // This is rehtona test
    free(result);
    
    result = spin_words("Welcome");
    printf("%s\\n", result); // emocleW
    free(result);
    
    result = spin_words("");
    printf("%s\\n", result); // ""
    free(result);
    
    return 0;
}
