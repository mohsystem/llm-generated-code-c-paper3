#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverseWord(char* start, char* end) {
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

void spinWords(char* sentence, char* result) {
    char* word_start = sentence;
    char* temp = sentence;
    int len;
    while (*temp) {
        while (*temp && !isspace(*temp)) {
            temp++;
        }
        len = temp - word_start;
        if (len >= 5) {
            reverseWord(word_start, temp - 1);
        }
        strncat(result, word_start, len);
        if (*temp) {
            strncat(result, " ", 1);
            temp++;
            word_start = temp;
        }
    }
}

int main() {
    char sentence1[] = "Hey fellow warriors";
    char result1[50] = "";
    spinWords(sentence1, result1);
    printf("%s\n", result1);

    char sentence2[] = "This is a test";
    char result2[50] = "";
    spinWords(sentence2, result2);
    printf("%s\n", result2);

    char sentence3[] = "This is another test";
    char result3[50] = "";
    spinWords(sentence3, result3);
    printf("%s\n", result3);

    char sentence4[] = "Java programming";
    char result4[50] = "";
    spinWords(sentence4, result4);
    printf("%s\n", result4);

    char sentence5[] = "Secure coding practices";
    char result5[50] = "";
    spinWords(sentence5, result5);
    printf("%s\n", result5);

    return 0;
}