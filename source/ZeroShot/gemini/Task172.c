#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure for a node in the hash table
typedef struct Node {
    char *str;
    struct Node *next;
} Node;

// Hash table functions (implementation omitted for brevity)
// ... (insert, search, free_table)

int distinctEchoSubstrings(char *text) {
    int n = strlen(text);
    Node **hash_table = create_table(1000); // Adjust size as needed
    int count = 0;

    for (int len = 2; len <= n; len += 2) {
        for (int i = 0; i <= n - len; i++) {
            char *sub = (char *)malloc(sizeof(char) * (len + 1));
            strncpy(sub, text + i, len);
            sub[len] = '\0';
            int mid = len / 2;

            if (strncmp(sub, sub + mid, mid) == 0) {
                if (!search(hash_table, sub)) {
                    insert(hash_table, sub);
                    count++;
                }
            } else {
                free(sub);
            }

        }
    }
    free_table(hash_table);
    return count;
}

int main() {
    printf("%d\n", distinctEchoSubstrings("abcabcabc")); // 3
    printf("%d\n", distinctEchoSubstrings("leetcodeleetcode")); // 2
    printf("%d\n", distinctEchoSubstrings("a")); // 0
    printf("%d\n", distinctEchoSubstrings("aa")); // 1
    printf("%d\n", distinctEchoSubstrings("aaaa")); // 2
    return 0;
}