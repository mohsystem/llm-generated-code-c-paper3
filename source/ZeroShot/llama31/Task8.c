#include <stdio.h>

char findMissingLetter(char letters[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (letters[i + 1] - letters[i] > 1) {
            return (char) (letters[i] + 1);
        }
    }
    return ' ';
}

int main() {
    char letters1[] = {'a', 'b', 'c', 'd', 'f', '\0'};
    char letters2[] = {'O', 'Q', 'R', 'S', '\0'};
    char letters3[] = {'a', 'b', 'c', 'e', 'f', '\0'};
    char letters4[] = {'A', 'B', 'C', 'E', 'F', '\0'};
    char letters5[] = {'x', 'y', 'z', 'a', 'b', '\0'};

    printf("%c\n", findMissingLetter(letters1, 5)); // 'e'
    printf("%c\n", findMissingLetter(letters2, 4)); // 'P'
    printf("%c\n", findMissingLetter(letters3, 5)); // 'd'
    printf("%c\n", findMissingLetter(letters4, 5)); // 'D'
    printf("%c\n", findMissingLetter(letters5, 5)); // This case is invalid as per problem constraints

    return 0;
}