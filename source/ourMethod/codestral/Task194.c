#include <stdio.h>
#include <string.h>

typedef struct {
    // Implementation of Master.guess is not provided
    int (*guess)(char *word);
} Master;

int guess(char *word) {
    // To be implemented
    return 0;
}

char *findSecretWord(char words[][7], Master *master, int allowedGuesses) {
    for (int i = 0; i < 10; i++) {
        int guess = master->guess(words[i]);
        if (guess == 6) {
            return "You guessed the secret word correctly.";
        }
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    Master master = {guess};

    char words1[4][7] = {"acckzz","ccbazz","eiowzz","abcczz"};
    char *secret1 = "acckzz";
    int allowedGuesses1 = 10;
    printf("%s\n", findSecretWord(words1, &master, allowedGuesses1));

    char words2[2][7] = {"hamada","khaled"};
    char *secret2 = "hamada";
    int allowedGuesses2 = 10;
    printf("%s\n", findSecretWord(words2, &master, allowedGuesses2));

    return 0;
}