#include <stdio.h>
#include <string.h>

struct Master {
    char secret[7];
};

int guess(struct Master *master, const char *word) {
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (word[i] == master->secret[i]) {
            matches++;
        }
    }
    return matches;
}


char *findSecretWord(const char *secret, char words[][7], int numWords, int allowedGuesses) {
    struct Master master;
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
    char words1[4][7] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    printf("%s\n", findSecretWord("acckzz", words1, 4, 10));

    char words2[2][7] = {"hamada", "khaled"};
    printf("%s\n", findSecretWord("hamada", words2, 2, 10));

    char words3[1][7] = {"abcdef"};
    printf("%s\n", findSecretWord("abcdef", words3, 1, 10));

    char words4[2][7] = {"leetcode", "leetcod"};
    printf("%s\n", findSecretWord("leetcode", words4, 2, 2));

    char words5[4][7] = {"banana", "orange", "apple", "grape"};
    printf("%s\n", findSecretWord("orange", words5, 4, 5));
    
    return 0;
}