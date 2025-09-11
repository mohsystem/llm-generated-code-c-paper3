#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void spin_words(char *sentence, char *result) {
    char *word = strtok(sentence, " ");
    while (word != NULL) {
        if (strlen(word) >= 5) {
            reverse_string(word);
        }
        strcat(result, word);
        strcat(result, " ");
        word = strtok(NULL, " ");
    }
    result[strlen(result) - 1] = '\0'; // Remove trailing space
}


int main() {
    char sentence1[] = "Hey fellow warriors";
    char result1[100] = "";
    spin_words(sentence1, result1);
    printf("%s\n", result1); // Output: Hey wollef sroirraw

    char sentence2[] = "This is a test";
    char result2[100] = "";
    spin_words(sentence2, result2);
    printf("%s\n", result2); // Output: This is a test

    char sentence3[] = "This is another test";
    char result3[100] = "";
    spin_words(sentence3, result3);
    printf("%s\n", result3); // Output: This is rehtona test

    char sentence4[] = "Welcome";
    char result4[100] = "";
    spin_words(sentence4, result4);
    printf("%s\n", result4); // Output: emocleW

    char sentence5[] = "to";
    char result5[100] = "";
    spin_words(sentence5, result5);
    printf("%s\n", result5); // Output: to


    return 0;
}