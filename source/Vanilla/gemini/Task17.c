#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *toJadenCase(char *phrase) {
    if (phrase == NULL || strlen(phrase) == 0) {
        return NULL;
    }

    char *result = (char *)malloc(strlen(phrase) * 2 + 1); // Allocate enough memory
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    char *word = strtok(phrase, " ");
    int index = 0;

    while (word != NULL) {
        word[0] = toupper(word[0]);
        strcpy(result + index, word);
        index += strlen(word);
        result[index++] = ' ';
        word = strtok(NULL, " ");
    }
    
    if(index > 0) {
        result[index - 1] = '\0'; // Remove trailing space and null-terminate
    } else {
        result[0] = '\0'; // Handle the case where the input is only spaces
    }

    return result;
}

int main() {
    char str1[] = "How can mirrors be real if our eyes aren't real";
    char str2[] = "most trees are blue";
    char str3[] = "";
    char str4[] = "All the rules in this world were made by someone no smarter than you. So make your own.";
    
    char *jaden_case1 = toJadenCase(str1);
    char *jaden_case2 = toJadenCase(str2);
    char *jaden_case3 = toJadenCase(str3);
    char *jaden_case4 = toJadenCase(str4);
    
    if (jaden_case1) {
        printf("%s\n", jaden_case1);
        free(jaden_case1);
    } else {
        printf("(null)\n");
    }
        
    if (jaden_case2) {
        printf("%s\n", jaden_case2);
        free(jaden_case2);
    } else {
        printf("(null)\n");
    }

    if (jaden_case3) {
        printf("%s\n", jaden_case3);
        free(jaden_case3);
    } else {
        printf("(null)\n");
    }


    if (jaden_case4) {
        printf("%s\n", jaden_case4);
        free(jaden_case4);
    } else {
        printf("(null)\n");
    }
    

    return 0;
}