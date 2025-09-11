#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_jaden_case(char *phrase) {
    int len = strlen(phrase);
    if (len == 0)
        return;

    if (phrase[0] >= 'a' && phrase[0] <= 'z')
        phrase[0] = phrase[0] - 'a' + 'A';

    for (int i = 1; i < len; i++) {
        if (phrase[i] == ' ' && phrase[i + 1] >= 'a' && phrase[i + 1] <= 'z')
            phrase[i + 1] = phrase[i + 1] - 'a' + 'A';
    }
}

int main() {
    char phrase[100];

    strcpy(phrase, "How can mirrors be real if our eyes aren't real");
    to_jaden_case(phrase);
    printf("%s\n", phrase);

    strcpy(phrase, "i'm grateful for every single thing that i've been blessed with");
    to_jaden_case(phrase);
    printf("%s\n", phrase);

    strcpy(phrase, "don't trust nobody and don't be afraid to use your head");
    to_jaden_case(phrase);
    printf("%s\n", phrase);

    strcpy(phrase, "it's easier to ask for forgiveness than it is to get permission");
    to_jaden_case(phrase);
    printf("%s\n", phrase);

    strcpy(phrase, "");
    to_jaden_case(phrase);
    printf("%s\n", phrase);

    return 0;
}