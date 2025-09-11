#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Assume Master struct and its functions are defined elsewhere
typedef struct Master Master;

int matchWord(const char* word1, const char* word2) {
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (word1[i] == word2[i]) {
            matches++;
        }
    }
    return matches;
}

void findSecretWord(char** wordlist, int wordlistSize, Master* master, int allowedGuesses) {
    for (int i = 0; i < allowedGuesses; i++) {
        char* guess = wordlist[0];
        int match = master->guess(guess);
        if (match == 6) {
            printf("You guessed the secret word correctly.\n");
            return;
        }
        // Filter words based on the number of matches
        int newWordlistSize = 0;
        for (int j = 0; j < wordlistSize; j++) {
            if (matchWord(guess, wordlist[j]) == match) {
                newWordlistSize++;
            }
        }
        char** newWordlist = malloc(newWordlistSize * sizeof(char*));
        int count = 0;
        for (int j = 0; j < wordlistSize; j++) {
            if (matchWord(guess, wordlist[j]) == match) {
                newWordlist[count++] = wordlist[j];
            }
        }
        free(wordlist);
        wordlist = newWordlist;
        wordlistSize = newWordlistSize;
    }
    printf("Either you took too many guesses, or you did not find the secret word.\n");
}

int main() {
    Master master;  // Assume Master struct is defined elsewhere
    char* words[] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    int allowedGuesses = 10;
    findSecretWord(words, 4, &master, allowedGuesses);

    char* words2[] = {"hamada", "khaled"};
    allowedGuesses = 10;
    findSecretWord(words2, 2, &master, allowedGuesses);
    return 0;
}