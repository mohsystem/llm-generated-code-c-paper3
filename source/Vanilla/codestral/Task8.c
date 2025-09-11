#include <stdio.h>

char findMissingLetter(char arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] - arr[i - 1] != 1) {
            return arr[i - 1] + 1;
        }
    }
    return ' ';
}

int main() {
    char arr1[] = {'a', 'b', 'c', 'd', 'f'};
    char arr2[] = {'O', 'Q', 'R', 'S'};
    printf("%c\n", findMissingLetter(arr1, 5));
    printf("%c\n", findMissingLetter(arr2, 4));
    return 0;
}