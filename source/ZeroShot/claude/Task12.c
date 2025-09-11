
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

char* highestScoringWord(const char* str) {
    static char result[100];
    char word[100];
    int maxScore = 0;
    int currentScore;
    char* maxWord = result;
    const char* start = str;
    int len;
    
    while (*str) {
        len = 0;
        while (*str && *str != ' ') {
            word[len++] = *str++;
        }
        word[len] = '\\0';
        
        currentScore = 0;
        for (int i = 0; i < len; i++) {
            currentScore += (word[i] - 'a' + 1);
        }
        
        if (currentScore > maxScore) {
            maxScore = currentScore;
            strcpy(maxWord, word);
        }
        
        while (*str == ' ') str++;
    }
    
    return maxWord;
}

int main() {
    // Test cases
    printf("%s\\n", highestScoringWord("man i need a taxi up to ubud"));
    printf("%s\\n", highestScoringWord("what time are we climbing up to the volcano"));
    printf("%s\\n", highestScoringWord("take me to semynak"));
    printf("%s\\n", highestScoringWord("aa b"));
    printf("%s\\n", highestScoringWord("z aa"));
    return 0;
}
