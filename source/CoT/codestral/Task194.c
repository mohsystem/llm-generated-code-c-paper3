// C solution
#include <stdio.h>
#include <string.h>

int guess(char* word) {
    char* secret = "acckzz";
    int matches = 0;
    for (int i = 0; i < 6; ++i)
        if (secret[i] == word[i]) matches++;
    return matches;
}

const char* findSecretWord(char words[][7], int n, int allowedGuesses) {
    for (int i = 0; i < allowedGuesses; ++i) {
        int matches = guess(words[i]);
        if (matches == 6) return "You guessed the secret word correctly.";
        int j = 0;
        for (int k = 0; k < n; ++k) {
            int common = 0;
            for (int l = 0; l < 6; ++l)
                if (words[i][l] == words[k][l]) common++;
            if (common == matches) strcpy(words[j++], words[k]);
        }
        n = j;
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    char words[4][7] = {"acckzz","ccbazz","eiowzz","abcczz"};
    int n = 4;
    int allowedGuesses = 10;
    printf("%s\n", findSecretWord(words, n, allowedGuesses));
    return 0;
}