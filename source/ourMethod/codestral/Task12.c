#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* highestScoringWord(const char* input) {
    static char word[100], maxWord[100];
    int maxScore = 0;
    while (sscanf(input, "%s", word) == 1) {
        int score = 0;
        for (char* p = word; *p; p++) {
            score += *p - 'a' + 1;
        }
        if (score > maxScore || (score == maxScore && strstr(input, word) < strstr(input, maxWord))) {
            maxScore = score;
            strcpy(maxWord, word);
        }
        input = strstr(input, word) + strlen(word);
    }
    static char result[100];
    strcpy(result, maxWord);
    return result;
}

int main() {
    printf("%s\n", highestScoringWord("abad hello world"));  // Output: "hello"
    printf("%s\n", highestScoringWord("apple banana cherry"));  // Output: "banana"
    printf("%s\n", highestScoringWord("cat dog elephant"));  // Output: "elephant"
    printf("%s\n", highestScoringWord("good bad better"));  // Output: "good"
    printf("%s\n", highestScoringWord("this is a test"));  // Output: "this"
    return 0;
}