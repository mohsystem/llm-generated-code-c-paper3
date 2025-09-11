#include <stdio.h>
#include <string.h>

char findMissingLetter(char chars[], int size) {
    const char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int startIndex = strchr(alphabet, chars[0]) - alphabet;
    for (int i = 0; i < size; i++) {
        if (chars[i] != alphabet[startIndex + i]) {
            return alphabet[startIndex + i];
        }
    }
    return ' '; // This line should not be reached
}

int main() {
    char test1[] = {'a', 'b', 'c', 'd', 'f', '\0'};
    char test2[] = {'O', 'Q', 'R', 'S', '\0'};
    char test3[] = {'a', 'b', 'c', 'e', '\0'};
    char test4[] = {'A', 'B', 'C', 'E', '\0'};
    char test5[] = {'x', 'y', 'z', 'a', '\0'};

    printf("%c\n", findMissingLetter(test1, 5)); // e
    printf("%c\n", findMissingLetter(test2, 4)); // P
    printf("%c\n", findMissingLetter(test3, 4)); // d
    printf("%c\n", findMissingLetter(test4, 4)); // D
    printf("%c\n", findMissingLetter(test5, 4)); // This case is invalid as per problem statement, but it will return 'b'

    return 0;
}