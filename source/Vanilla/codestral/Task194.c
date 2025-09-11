#include <stdio.h>
#include <string.h>

int match(char* a, char* b) {
    int matches = 0;
    for (int i = 0; i < 6; i++) {
        if (a[i] == b[i]) {
            matches++;
        }
    }
    return matches;
}

char* findSecretWord(char** words, int wordsSize, Master* master) {
    for (int i = 0, j = 0; i < master->guesses(); i++) {
        j = master->guess(words[i]);
        char* candidates[wordsSize];
        int count = 0;
        for (int k = 0; k < wordsSize; k++) {
            if (match(words[i], words[k]) == j) {
                candidates[count++] = words[k];
            }
        }
        for (int k = 0; k < count; k++) {
            words[k] = candidates[k];
        }
        wordsSize = count;
    }
    return master->result();
}

int main() {
    // Test cases
    Master master;
    char* words1[] = {"acckzz","ccbazz","eiowzz","abcczz"};
    printf("%s\n", findSecretWord(words1, 4, &master));
    char* words2[] = {"hamada","khaled"};
    printf("%s\n", findSecretWord(words2, 2, &master));
    return 0;
}