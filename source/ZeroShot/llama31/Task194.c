#include <stdio.h>
#include <string.h>

// Assuming Master struct and its functions are implemented elsewhere
typedef struct {
    char secret[7];
} Master;

int match(const char* word1, const char* word2) {
    int match = 0;
    for (int i = 0; i < 6; i++) {
        if (word1[i] == word2[i]) {
            match++;
        }
    }
    return match;
}

int guess(Master* master, const char* word) {
    int match = 0;
    for (int i = 0; i < 6; i++) {
        if (word[i] == master->secret[i]) {
            match++;
        }
    }
    return match;
}

void findSecretWord(char** wordlist, int size, Master* master, int allowedGuesses) {
    for (int i = 0; i < allowedGuesses; i++) {
        const char* guess = wordlist[0];
        int match = guess(master, guess);
        if (match == 6) {
            printf("You guessed the secret word correctly.\n");
            return;
        }
        // Filter words based on the match
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (match(wordlist[j], guess) == match) {
                count++;
            }
        }
        char** newWordlist = (char**)malloc(count * sizeof(char*));
        int k = 0;
        for (int j = 0; j < size; j++) {
            if (match(wordlist[j], guess) == match) {
                newWordlist[k++] = wordlist[j];
            }
        }
        free(wordlist);
        wordlist = newWordlist;
        size = count;
    }
    printf("Either you took too many guesses, or you did not find the secret word.\n");
}

int main() {
    Master master;
    strcpy(master.secret, "acckzz");
    char* words[] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    findSecretWord(words, 4, &master, 10);

    strcpy(master.secret, "hamada");
    char* words2[] = {"hamada", "khaled"};
    findSecretWord(words2, 2, &master, 10);
    return 0;
}