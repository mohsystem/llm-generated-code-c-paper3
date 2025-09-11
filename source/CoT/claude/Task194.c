
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Master {
    char secret[7];
    int guesses;
    int allowedGuesses;
};

void initMaster(struct Master* master, const char* secret, int allowedGuesses) {
    strcpy(master->secret, secret);
    master->allowedGuesses = allowedGuesses;
    master->guesses = 0;
}

int guess(struct Master* master, const char* word) {
    master->guesses++;
    if (master->guesses > master->allowedGuesses) {
        return -1;
    }
    
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (word[i] == master->secret[i]) {
            matches++;
        }
    }
    return matches;
}

const char* findSecretWord(char** words, int wordsSize, struct Master* master) {
    for (int i = 0; i < wordsSize; i++) {
        int matches = guess(master, words[i]);
        if (matches == 6) {
            return "You guessed the secret word correctly.";
        }
    }
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    struct Master master;
    
    // Test case 1
    char* words1[] = {"acckzz","ccbazz","eiowzz","abcczz"};
    initMaster(&master, "acckzz", 10);
    printf("%s\\n", findSecretWord(words1, 4, &master));
    
    // Test case 2
    char* words2[] = {"hamada","khaled"};
    initMaster(&master, "hamada", 10);
    printf("%s\\n", findSecretWord(words2, 2, &master));
    
    // Test case 3
    char* words3[] = {"aaaaaa", "bbbbbb", "cccccc"};
    initMaster(&master, "bbbbbb", 10);
    printf("%s\\n", findSecretWord(words3, 3, &master));
    
    // Test case 4
    char* words4[] = {"abcdef", "ghijkl"};
    initMaster(&master, "ghijkl", 10);
    printf("%s\\n", findSecretWord(words4, 2, &master));
    
    // Test case 5
    char* words5[] = {"zzzzzz"};
    initMaster(&master, "zzzzzz", 10);
    printf("%s\\n", findSecretWord(words5, 1, &master));
    
    return 0;
}
