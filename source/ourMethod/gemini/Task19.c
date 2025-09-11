#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}


void spin_words(char *sentence, char *result) {
    char *word = strtok(sentence, " ");
    while (word != NULL) {
        if (strlen(word) >= 5) {
            reverse_string(word);
        }
        strcat(result, word);
        word = strtok(NULL, " ");
        if (word != NULL) {
            strcat(result, " ");
        }
    }
}

int main() {
    char test_cases[][50] = {
        "Hey fellow warriors",
        "This is a test",
        "This is another test",
        "Hello",
        "What's the story morning glory?"
    };
    char expected_outputs[][50] = {
        "Hey wollef sroirraw",
        "This is a test",
        "This is rehtona test",
        "Hello",
        "What's the yrrots gninrom yrolg?"
    };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        char sentence[50];
        strcpy(sentence, test_cases[i]);
        char result[100] = "";
        spin_words(sentence, result);

        printf("Test case %d: \"%s\"\n", i + 1, test_cases[i]);
        printf("Expected output: \"%s\"\n", expected_outputs[i]);
        printf("Actual output: \"%s\"\n", result);
        printf("%s\n\n", strcmp(result, expected_outputs[i]) == 0 ? "PASS" : "FAIL");
    }

    return 0;
}