
// Note: Due to C language limitations and the object-oriented nature of the problem,
// a simplified version is provided that demonstrates the core logic.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_LENGTH 6
#define MAX_WORDS 100

// Simulated Master class functionality
int guess_count = 0;
char secret[WORD_LENGTH + 1];
char words[MAX_WORDS][WORD_LENGTH + 1];
int allowed_guesses;
int word_count;

void init_master(const char* secret_word, char word_list[][WORD_LENGTH + 1], int words_count, int max_guesses) {
    strcpy(secret, secret_word);
    for (int i = 0; i < words_count; i++) {
        strcpy(words[i], word_list[i]);
    }
    word_count = words_count;
    allowed_guesses = max_guesses;
    guess_count = 0;
}

int make_guess(const char* word) {
    if (++guess_count > allowed_guesses) {
        return -2;  // Special error code for too many guesses
    }
    
    int found = 0;
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i], word) == 0) {
            found = 1;
            break;
        }
    }
    if (!found) return -1;
    
    int matches = 0;
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word[i] == secret[i]) matches++;
    }
    return matches;
}

int get_matches(const char* word1, const char* word2) {
    int matches = 0;
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word1[i] == word2[i]) matches++;
    }
    return matches;
}

const char* find_secret_word(const char* secret_word, char word_list[][WORD_LENGTH + 1], 
                           int words_count, int max_guesses) {
    init_master(secret_word, word_list, words_count, max_guesses);
    
    char current_words[MAX_WORDS][WORD_LENGTH + 1];
    int current_count = words_count;
    
    for (int i = 0; i < words_count; i++) {
        strcpy(current_words[i], word_list[i]);
    }
    
    while (current_count > 0) {
        int matches = make_guess(current_words[0]);
        
        if (matches == -2) {
            return "Either you took too many guesses, or you did not find the secret word.";
        }
        
        if (matches == WORD_LENGTH) {
            return "You guessed the secret word correctly.";
        }
        
        char new_candidates[MAX_WORDS][WORD_LENGTH + 1];
        int new_count = 0;
        
        for (int i = 0; i < current_count; i++) {
            if (get_matches(current_words[0], current_words[i]) == matches) {
                strcpy(new_candidates[new_count++], current_words[i]);
            }
        }
        
        current_count = new_count;
        for (int i = 0; i < new_count; i++) {
            strcpy(current_words[i], new_candidates[i]);
        }
    }
    
    return "Either you took too many guesses, or you did not find the secret word.";
}

int main() {
    // Test case 1
    char words1[][WORD_LENGTH + 1] = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    printf("%s\\n", find_secret_word("acckzz", words1, 4, 10));
    
    // Test case 2
    char words2[][WORD_LENGTH + 1] = {"hamada", "khaled"};
    printf("%s\\n", find_secret_word("hamada", words2, 2, 10));
    
    // Test case 3
    char words3[][WORD_LENGTH + 1] = {"abcdef", "ghijkl", "mnopqr"};
    printf("%s\\n", find_secret_word("abcdef", words3, 3, 10));
    
    // Test case 4
    char words4[][WORD_LENGTH + 1] = {"aaaaaa", "bbbbbb"};
    printf("%s\\n", find_secret_word("aaaaaa", words4, 2, 10));
    
    // Test case 5
    char words5[][WORD_LENGTH + 1] = {"xxxxxx"};
    printf("%s\\n", find_secret_word("xxxxxx", words5, 1, 10));
    
    return 0;
}
