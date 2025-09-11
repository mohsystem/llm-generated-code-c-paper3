#include <stdio.h>
#include <string.h>

typedef struct {
    char secret[7];
    char words[100][7];
    int wordCount;
} Master;

int guess(Master *master, const char *word) {
    for (int i = 0; i < master->wordCount; i++) {
        if (strcmp(master->words[i], word) == 0) {
            int matches = 0;
            for (int j = 0; j < 6; j++) {
                if (word[j] == master->secret[j]) {
                    matches++;
                }
            }
            return matches;
        }
    }
    return -1;
}

const char* findSecretWord(char words[][7], int wordCount, Master *master, int allowedGuesses) {
    int guessCount = 0;
    for (int i = 0; i < wordCount; i++) {
        int result = guess(master, words[i]);
        guessCount++;
        if (result == 6) {
            return "You guessed the secret word correctly.";
        }
        if (guessCount > allowedGuesses) {
            return "Either you took too many guesses, or you did not find the secret word.";
        }
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    char words1[4][7] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    Master master1 = {"acckzz", {"acckzz", "ccbazz", "eiowzz", "abcczz"}, 4};
    printf("%s\n", findSecretWord(words1, 4, &master1, 10));

    char words2[2][7] = {"hamada", "khaled"};
    Master master2 = {"hamada", {"hamada", "khaled"}, 2};
    printf("%s\n", findSecretWord(words2, 2, &master2, 10));

    char words3[4][7] = {"abcdef", "ghijkl", "mnopqr", "stuvwx"};
    Master master3 = {"mnopqr", {"abcdef", "ghijkl", "mnopqr", "stuvwx"}, 4};
    printf("%s\n", findSecretWord(words3, 4, &master3, 10));

    char words4[4][7] = {"aaaaaa", "bbbbbb", "cccccc", "dddddd"};
    Master master4 = {"dddddd", {"aaaaaa", "bbbbbb", "cccccc", "dddddd"}, 4};
    printf("%s\n", findSecretWord(words4, 4, &master4, 10));

    char words5[3][7] = {"zzzzzz", "yyyyyy", "xxxxxx"};
    Master master5 = {"xxxxxx", {"zzzzzz", "yyyyyy", "xxxxxx"}, 3};
    printf("%s\n", findSecretWord(words5, 3, &master5, 10));

    return 0;
}