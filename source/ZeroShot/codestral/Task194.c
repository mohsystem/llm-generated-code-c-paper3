#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Master {
    char *secret;
} Master;

Master *createMaster(char *secret) {
    Master *master = malloc(sizeof(Master));
    master->secret = secret;
    return master;
}

int guess(Master *master, char *word) {
    int matches = 0;
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == master->secret[i]) {
            matches++;
        }
    }
    return matches;
}

const char *guessSecretWord(char *words[], int wordsSize, int allowedGuesses, char *secret) {
    Master *master = createMaster(secret);
    srand(time(0));
    for (int i = 0; i < allowedGuesses; i++) {
        char *guess = words[rand() % wordsSize];
        int matches = guess(master, guess);
        if (matches == 6) {
            free(master);
            return "You guessed the secret word correctly.";
        }
    }
    free(master);
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    char *words1[] = {"acckzz","ccbazz","eiowzz","abcczz"};
    char *words2[] = {"hamada","khaled"};
    printf("%s\n", guessSecretWord(words1, 4, 10, "acckzz"));
    printf("%s\n", guessSecretWord(words2, 2, 10, "hamada"));
    return 0;
}