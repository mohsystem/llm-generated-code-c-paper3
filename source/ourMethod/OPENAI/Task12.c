#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000000

static int score_char(unsigned char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return (int)(ch - 'a' + 1);
    }
    return 0;
}

char* highest_scoring_word(const char* s) {
    if (s == NULL) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    size_t n = strlen(s);
    if (n > MAX_LEN) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    int bestScore = -1;
    size_t bestStart = 0;
    size_t bestLen = 0;

    int curScore = 0;
    size_t curStart = 0;
    size_t curLen = 0;

    for (size_t i = 0; i < n; ++i) {
        unsigned char ch = (unsigned char)s[i];
        if (!isspace(ch)) {
            if (curLen == 0) {
                curStart = i;
            }
            curScore += score_char(ch);
            curLen += 1;
        } else {
            if (curLen > 0) {
                if (curScore > bestScore) {
                    bestScore = curScore;
                    bestStart = curStart;
                    bestLen = curLen;
                }
                curLen = 0;
                curScore = 0;
            }
        }
    }

    if (curLen > 0) {
        if (curScore > bestScore) {
            bestScore = curScore;
            bestStart = curStart;
            bestLen = curLen;
        }
    }

    if (bestScore < 0) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    char* result = (char*)malloc(bestLen + 1);
    if (result == NULL) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    memcpy(result, s + bestStart, bestLen);
    result[bestLen] = '\0';
    return result;
}

int main(void) {
    const char* tests[5] = {
        "man i need a taxi up to ubud",
        "what time are we climbing up the volcano",
        "take me to semynak",
        "aa b",
        "abad zzz a b c"
    };

    for (int i = 0; i < 5; ++i) {
        char* res = highest_scoring_word(tests[i]);
        if (res == NULL) {
            printf("Input: \"%s\" -> Highest: <allocation failed>\n", tests[i]);
        } else {
            printf("Input: \"%s\" -> Highest: \"%s\"\n", tests[i], res);
            free(res);
        }
    }
    return 0;
}