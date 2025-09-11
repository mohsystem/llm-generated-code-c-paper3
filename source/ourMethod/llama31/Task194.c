#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to represent the Master
typedef struct {
    char secret[7];
} Master;

// Function to initialize the Master
Master* Master_new(const char* secret) {
    Master* master = (Master*)malloc(sizeof(Master));
    strcpy(master->secret, secret);
    return master;
}

// Function to guess the word
int Master_guess(Master* master, const char* word) {
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (master->secret[i] == word[i]) {
            matches++;
        }
    }
    return matches;
}

// Function to filter words based on matches
void filterWords(char** wordlist, int* wordlistSize, const char* guess, int match) {
    int newWordlistSize = 0;
    for (int i = 0; i < *wordlistSize; i++) {
        if (matchWords(wordlist[i], guess) == match) {
            newWordlistSize++;
        }
    }
    char** newWordlist = (char**)malloc(newWordlistSize * sizeof(char*));
    int j = 0;
    for (int i = 0; i < *wordlistSize; i++) {
        if (matchWords(wordlist[i], guess) == match) {
            newWordlist[j++] = wordlist[i];
        }
    }
    *wordlistSize = newWordlistSize;
    free(wordlist);
    *wordlist = newWordlist;
}

// Function to match two words
int matchWords(const char* word1, const char* word2) {
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (word1[i] == word2[i]) {
            matches++;
        }
    }
    return matches;
}

// Function to find the secret word
void findSecretWord(char** wordlist, int wordlistSize, Master* master, int allowedGuesses) {
    for (int i = 0; i < allowedGuesses; i++) {
        const char* guess = wordlist[0];
        int match = Master_guess(master, guess);
        if (match == 6) {
            printf("You guessed the secret word correctly.\n");
            return;
        }
        filterWords(wordlist, &wordlistSize, guess, match);
    }
    printf("Either you took too many guesses, or you did not find the secret word.\n");
}

int main() {
    char* words[] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    int wordlistSize = sizeof(words) / sizeof(words[0]);
    Master* master = Master_new("acckzz");
    findSecretWord(words, wordlistSize, master, 10);

    char* newWords[] = {"hamada", "khaled"};
    wordlistSize = sizeof(newWords) / sizeof(newWords[0]);
    master = Master_new("hamada");
    findSecretWord(newWords, wordlistSize, master, 10);

    return 0;
}