#include <stdio.h>
#include <string.h>

typedef struct {
    char secret[7];
} Master;

int guess(Master* master, const char* word) {
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (word[i] == master->secret[i]) {
            matches++;
        }
    }
    return matches;
}

char* findSecretWord(const char* secret, char words[][7], int numWords, int allowedGuesses) {
    Master master;
    strcpy(master.secret, secret);
    int guesses = 0;
    for (int i = 0; i < numWords; i++) {
        if (guesses >= allowedGuesses) {
            return "Either you took too many guesses, or you did not find the secret word.";
        }
        int matches = guess(&master, words[i]);
        guesses++;
        if (matches == 6) {
            return "You guessed the secret word correctly.";
        }
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    // Test cases
    char words1[4][7] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    printf("%s\n", findSecretWord("acckzz", words1, 4, 10)); // Output: You guessed the secret word correctly.

    char words2[2][7] = {"hamada", "khaled"};
    printf("%s\n", findSecretWord("hamada", words2, 2, 10)); // Output: You guessed the secret word correctly.

    char words3[3][7] = {"qwerty", "asdfgh", "zxcvbn"};
    printf("%s\n", findSecretWord("qwerty", words3, 3, 2)); // Output: You guessed the secret word correctly.

    char words4[3][7] = {"apple", "banana", "orange"};
    printf("%s\n", findSecretWord("grape", words4, 3, 3)); // Output: Either you took too many guesses, or you did not find the secret word.


    char words5[5][7] = {"abcdef", "ghijkl", "mnopqr", "stuvwx", "yz1234"};
    printf("%s\n", findSecretWord("abcdef", words5, 5, 5)); // Output: You guessed the secret word correctly.


    return 0;
}