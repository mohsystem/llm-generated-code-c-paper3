#include <stdio.h>
#include <string.h>

typedef struct {
    const char* secret;
    int calls;
    const char* words[100];
    int wordsCount;
} Master;

int master_guess(Master* master, const char* word) {
    master->calls++;
    for (int i = 0; i < master->wordsCount; i++) {
        if (strcmp(master->words[i], word) == 0) {
            int matches = 0;
            for (int j = 0; j < 6; j++) {
                if (master->secret[j] == word[j]) matches++;
            }
            return matches;
        }
    }
    return -1;
}

const char* find_secret_word(const char* words[], int wordsCount, Master* master, int allowedGuesses) {
    for (int i = 0; i < allowedGuesses; i++) {
        const char* guessWord = words[i % wordsCount];
        if (master_guess(master, guessWord) == 6) {
            return "You guessed the secret word correctly.";
        }
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    const char* wordSets[5][4] = {
        {"acckzz", "ccbazz", "eiowzz", "abcczz"},
        {"hamada", "khaled"},
        {"orange", "banana", "grapes", "peachy"},
        {"monday", "tuesday", "wednes"},
        {"github", "gitlab", "bitbuc"}
    };
    const char* secrets[] = {"acckzz", "hamada", "banana", "tuesday", "bitbuc"};
    int allowedGuessesList[] = {10, 10, 10, 10, 10};

    for (int i = 0; i < 5; i++) {
        Master master = {secrets[i], 0, {0}, 4};
        for (int j = 0; j < 4; j++) {
            master.words[j] = wordSets[i][j];
        }
        master.wordsCount = 4;

        const char* result = find_secret_word(master.words, master.wordsCount, &master, allowedGuessesList[i]);
        printf("Test Case %d: %s\n", i + 1, result);
        printf("Guesses Used: %d\n", master.calls);
    }

    return 0;
}