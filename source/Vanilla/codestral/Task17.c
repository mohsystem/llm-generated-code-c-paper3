#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toJadenCase(char *phrase) {
    if (phrase == NULL || strlen(phrase) == 0) {
        strcpy(phrase, "");
        return;
    }

    int i;
    for (i = 0; phrase[i]; i++) {
        if (i == 0 || phrase[i - 1] == ' ')
            phrase[i] = toupper(phrase[i]);
        else
            phrase[i] = tolower(phrase[i]);
    }
}

int main() {
    char phrase[100];
    strcpy(phrase, "How can mirrors be real if our eyes aren't real");
    toJadenCase(phrase);
    printf("%s\n", phrase); // "How Can Mirrors Be Real If Our Eyes Aren't Real"

    strcpy(phrase, "");
    toJadenCase(phrase);
    printf("%s\n", phrase); // ""

    return 0;
}