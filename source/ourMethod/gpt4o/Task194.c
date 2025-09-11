#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char secret[7];
} Master;

int guess(Master* master, const char* word) {
    if (strcmp(word, master->secret) == 0) return 6;
    if (strcmp(word, "acckzz") != 0 && strcmp(word, "ccbazz") != 0 && strcmp(word, "eiowzz") != 0 && strcmp(word, "abcczz") != 0 && strcmp(word, "hamada") != 0 && strcmp(word, "khaled") != 0) return -1;
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (word[i] == master->secret[i]) count++;
    }
    return count;
}

const char* findSecretWord(char** words, int wordsSize, Master* master, int allowedGuesses) {
    srand(time(NULL));
    for (int i = 0; i < allowedGuesses && wordsSize > 0; i++) {
        int randIndex = rand() % wordsSize;
        char* candidate = words[randIndex];
        int matches = guess(master, candidate);
        if (matches == 6) {
            return "You guessed the secret word correctly.";
        }
        char** nextWords = malloc(wordsSize * sizeof(char*));
        int nextWordsSize = 0;
        for (int j = 0; j < wordsSize; j++) {
            if (strcmp(candidate, words[j]) != 0) {
                int matchCount = 0;
                for (int k = 0; k < 6; k++) {
                    if (candidate[k] == words[j][k]) matchCount++;
                }
                if (matchCount == matches) {
                    nextWords[nextWordsSize++] = words[j];
                }
            }
        }
        words = nextWords;
        wordsSize = nextWordsSize;
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    Master master1 = {"acckzz"};
    char* words1[] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    printf("%s\n", findSecretWord(words1, 4, &master1, 10));  // You guessed the secret word correctly.

    Master master2 = {"hamada"};
    char* words2[] = {"hamada", "khaled"};
    printf("%s\n", findSecretWord(words2, 2, &master2, 10));  // You guessed the secret word correctly.

    return 0;
}