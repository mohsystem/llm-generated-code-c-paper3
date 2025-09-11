#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_jaden_case(char *phrase) {
    if (phrase == NULL || strlen(phrase) == 0)
        return;

    int len = strlen(phrase);
    int i;

    for (i = 0; i < len; i++) {
        if (i == 0 || phrase[i - 1] == ' ')
            phrase[i] = toupper(phrase[i]);
        else
            phrase[i] = tolower(phrase[i]);
    }
}

int main() {
    char phrase1[] = "How can mirrors be real if our eyes aren't real";
    to_jaden_case(phrase1);
    printf("%s\n", phrase1);

    char phrase2[] = "I rather be a warrior in a garden than a garden warrior";
    to_jaden_case(phrase2);
    printf("%s\n", phrase2);

    char phrase3[] = "";
    to_jaden_case(phrase3);
    printf("%s\n", phrase3);

    char phrase4[] = "I'm the greatest artist of all time!";
    to_jaden_case(phrase4);
    printf("%s\n", phrase4);

    return 0;
}