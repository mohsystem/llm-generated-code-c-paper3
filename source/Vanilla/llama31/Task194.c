#include <stdio.h>
#include <string.h>

// Assume Master struct and its functions are defined elsewhere
typedef struct {
    // Master implementation
} Master;

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
        const char* guess = wordlist[0];
        int match = master->guess(guess);
        if (match == 6) {
            printf("You guessed the secret word correctly.\n");
            return;
        }
        int newWordlistSize = 0;
        for (int j = 0; j < wordlistSize; j++) {
            if (matchWord(wordlist[j], guess) == match) {
                newWordlistSize++;
            }
        }
        char** newWordlist = (char**)malloc(newWordlistSize * sizeof(char*));
        int k = 0;
        for (int j = 0; j < wordlistSize; j++) {
            if (matchWord(wordlist[j], guess) == match) {
                newWordlist[k++] = wordlist[j];
            }
        }
        wordlistSize = newWordlistSize;
        free(wordlist);
        wordlist = newWordlist;
    }
    printf("Either you took too many guesses, or you did not find the secret word.\n");
}

int main() {
    Master master;  // Assume Master struct is implemented

    // Test case 1
    char* words1[] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    findSecretWord(words1, 4, &master, 10);

    // Test case 2
    char* words2[] = {"hamada", "khaled"};
    findSecretWord(words2, 2, &master, 10);

    return 0;
}