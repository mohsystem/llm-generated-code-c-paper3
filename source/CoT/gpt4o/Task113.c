#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

void concatenateStrings(int count, char result[], char strings[][MAX_LENGTH]) {
    for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
    }
}

int main() {
    int n;
    printf("Enter number of strings to concatenate: ");
    scanf("%d", &n);
    getchar(); // consume the remaining newline

    char strings[n][MAX_LENGTH];
    char result[MAX_LENGTH] = "";

    for (int i = 0; i < n; i++) {
        printf("Enter string %d: ", i + 1);
        fgets(strings[i], MAX_LENGTH, stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0'; // remove newline character
    }

    concatenateStrings(n, result, strings);
    printf("Concatenated result: %s\n", result);

    // Test cases
    char test1[MAX_LENGTH] = "";
    concatenateStrings(2, test1, (char[][MAX_LENGTH]){"Hello", "World"});
    printf("%s\n", test1);

    char test2[MAX_LENGTH] = "";
    concatenateStrings(3, test2, (char[][MAX_LENGTH]){"C", " ", "Programming"});
    printf("%s\n", test2);

    char test3[MAX_LENGTH] = "";
    concatenateStrings(2, test3, (char[][MAX_LENGTH]){"Secure", "Coding"});
    printf("%s\n", test3);

    char test4[MAX_LENGTH] = "";
    concatenateStrings(5, test4, (char[][MAX_LENGTH]){"Chain", "-", "Of", "-", "Through"});
    printf("%s\n", test4);

    char test5[MAX_LENGTH] = "";
    concatenateStrings(2, test5, (char[][MAX_LENGTH]){"Test", "123"});
    printf("%s\n", test5);

    return 0;
}