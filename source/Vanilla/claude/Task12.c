
#include <stdio.h>
#include <string.h>

char* highestScoringWord(const char* str) {
    static char result[100];
    char word[100];
    int maxScore = 0;
    int currentPos = 0;
    int len = strlen(str);
    
    strcpy(result, "");
    
    for(int i = 0; i <= len; i++) {
        if(str[i] == ' ' || str[i] == '\\0') {
            word[currentPos] = '\\0';
            int score = 0;
            
            for(int j = 0; j < currentPos; j++) {
                score += (word[j] - 'a' + 1);
            }
            
            if(score > maxScore) {
                maxScore = score;
                strcpy(result, word);
            }
            
            currentPos = 0;
        } else {
            word[currentPos++] = str[i];
        }
    }
    
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", highestScoringWord("man i need a taxi up to ubud")); // taxi
    printf("%s\\n", highestScoringWord("what time are we climbing up to the volcano")); // volcano
    printf("%s\\n", highestScoringWord("take me to semynak")); // semynak
    printf("%s\\n", highestScoringWord("aa b")); // aa
    printf("%s\\n", highestScoringWord("b aa")); // b
    return 0;
}
