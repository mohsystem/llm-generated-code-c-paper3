#include <stdio.h>
#include <string.h>

typedef struct {
    char* secret;
    char** wordSet;
    int wordCount;
    int allowedGuesses;
    int guessCount;
} Master;

Master* createMaster(char* secret, char* words[], int wordCount, int allowedGuesses) {
    Master* master = (Master*)malloc(sizeof(Master));
    master->secret = secret;
    master->wordSet = words;
    master->wordCount = wordCount;
    master->allowedGuesses = allowedGuesses;
    master->guessCount = 0;
    return master;
}

int masterGuess(Master* master, char* word) {
    master->guessCount++;
    if (master->guessCount > master->allowedGuesses) {
        printf("Either you took too many guesses, or you did not find the secret word.\n");
        return -1;
    }
    int found = 0;
    for (int i = 0; i < master->wordCount; i++) {
        if (strcmp(master->wordSet[i], word) == 0) {
            found = 1;
            break;
        }
    }
    if (!found) {
        return -1;
    }
    int matchCount = 0;
    for (int i = 0; i < strlen(master->secret); i++) {
        if (master->secret[i] == word[i]) {
            matchCount++;
        }
    }
    if (matchCount == strlen(master->secret)) {
        printf("You guessed the secret word correctly.\n");
    }
    return matchCount;
}

void findSecretWord(char* words[], int wordCount, Master* master) {
    for (int i = 0; i < wordCount; i++) {
        int matches = masterGuess(master, words[i]);
        if (matches == strlen(words[i])) {
            return;
        }
    }
}

int main() {
    char* words1[] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    Master* master1 = createMaster("acckzz", words1, 4, 10);
    findSecretWord(words1, 4, master1);

    char* words2[] = {"hamada", "khaled"};
    Master* master2 = createMaster("hamada", words2, 2, 10);
    findSecretWord(words2, 2, master2);

    char* words3[] = {"orange", "banana", "grapee", "apples"};
    Master* master3 = createMaster("banana", words3, 4, 10);
    findSecretWord(words3, 4, master3);

    char* words4[] = {"abcdef", "ghijkl", "mnopqr", "stuvwx"};
    Master* master4 = createMaster("mnopqr", words4, 4, 10);
    findSecretWord(words4, 4, master4);

    char* words5[] = {"aaaaaa", "bbbbbb", "cccccc", "dddddd"};
    Master* master5 = createMaster("cccccc", words5, 4, 10);
    findSecretWord(words5, 4, master5);

    return 0;
}