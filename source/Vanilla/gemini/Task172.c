#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Implementing a simple hash set for C (limited functionality for this problem)
typedef struct {
    char **keys;
    int size;
    int capacity;
} HashSet;

HashSet *createHashSet(int capacity) {
    HashSet *set = (HashSet *)malloc(sizeof(HashSet));
    set->keys = (char **)calloc(capacity, sizeof(char *));
    set->size = 0;
    set->capacity = capacity;
    return set;
}

int hash(char *str) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = 31 * hash + str[i];
    }
    return abs(hash);
}

void add(HashSet *set, char *key) {
    int index = hash(key) % set->capacity;
    while (set->keys[index] != NULL && strcmp(set->keys[index], key) != 0) {
        index = (index + 1) % set->capacity;
    }
    if (set->keys[index] == NULL) {
        set->keys[index] = strdup(key); 
        set->size++;
    }
}


int distinctEchoSubstrings(char *text) {
    HashSet *distinctEchoes = createHashSet(2001); // Adjust capacity as needed
    int n = strlen(text);
    for (int len = 1; len <= n / 2; len++) {
        for (int i = 0; i <= n - 2 * len; i++) {
            char s1[len + 1];
            char s2[len + 1];
            strncpy(s1, text + i, len);
            s1[len] = '\0';
            strncpy(s2, text + i + len, len);
            s2[len] = '\0';
            if (strcmp(s1, s2) == 0) {
                char combined[2 * len + 1];
                strcpy(combined, s1);
                strcat(combined, s2);
                add(distinctEchoes, combined);
            }
        }
    }
    return distinctEchoes->size;
}

int main() {
    printf("%d\n", distinctEchoSubstrings("abcabcabc")); // 3
    printf("%d\n", distinctEchoSubstrings("leetcodeleetcode")); // 2
    printf("%d\n", distinctEchoSubstrings("a")); // 0
    printf("%d\n", distinctEchoSubstrings("aa")); // 1
    printf("%d\n", distinctEchoSubstrings("aaaa")); // 2
    return 0;
}