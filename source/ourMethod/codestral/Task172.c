#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SET_SIZE 100000

typedef struct {
    char *str;
    unsigned int hash;
} SetElement;

typedef struct {
    SetElement *elements;
    int size;
    int capacity;
} Set;

unsigned int hash_function(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void init_set(Set *set) {
    set->elements = (SetElement *)malloc(MAX_SET_SIZE * sizeof(SetElement));
    set->size = 0;
    set->capacity = MAX_SET_SIZE;
}

void insert_set(Set *set, const char *str) {
    unsigned int hash = hash_function(str);

    for (int i = 0; i < set->size; i++) {
        if (set->elements[i].hash == hash && strcmp(set->elements[i].str, str) == 0) {
            return;
        }
    }

    set->elements[set->size].str = strdup(str);
    set->elements[set->size].hash = hash;
    set->size++;
}

int numDistinct(char *text) {
    int n = strlen(text);
    Set set;
    init_set(&set);

    for (int len = 1; len <= n / 2; len++) {
        for (int i = 0; i <= n - 2 * len; i++) {
            char *a = strndup(text + i, len);
            char *b = strndup(text + i + len, len);
            if (strcmp(a, b) == 0) {
                insert_set(&set, a);
            }
            free(a);
            free(b);
        }
    }

    int result = set.size;
    for (int i = 0; i < set.size; i++) {
        free(set.elements[i].str);
    }
    free(set.elements);

    return result;
}

int main() {
    printf("%d\n", numDistinct("abcabcabc"));  // Output: 3
    printf("%d\n", numDistinct("leetcodeleetcode"));  // Output: 2
    // Add more test cases as needed
    return 0;
}