#include <stdio.h>
#include <string.h>

void concatenateStrings(char *result, char *strings[], int size) {
    result[0] = '\0';
    for (int i = 0; i < size; i++) {
        strcat(result, strings[i]);
    }
}

int main() {
    char result[100];
    char *test1[] = {"Hello", " ", "World", "!"};
    concatenateStrings(result, test1, 4);
    printf("%s\n", result); // "Hello World!"

    char *test2[] = {"I", " ", "love", " ", "coding"};
    concatenateStrings(result, test2, 5);
    printf("%s\n", result); // "I love coding"

    char *test3[] = {"Java", "Python", "C++"};
    concatenateStrings(result, test3, 3);
    printf("%s\n", result); // "JavaPythonC++"

    char *test4[] = {"1", "2", "3", "4", "5"};
    concatenateStrings(result, test4, 5);
    printf("%s\n", result); // "12345"

    char *test5[] = {"apple", "banana", "cherry"};
    concatenateStrings(result, test5, 3);
    printf("%s\n", result); // "applebananacherry"

    return 0;
}