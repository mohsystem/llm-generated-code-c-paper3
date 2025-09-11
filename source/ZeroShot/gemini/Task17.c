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

    char *token = strtok(phrase, " ");
    int i = 0;
    while (token != NULL) {
        if (strlen(token) > 0) {
            token[0] = toupper(token[0]);
            strcpy(result + i, token);
            i += strlen(token);
            result[i++] = ' ';
        }
        token = strtok(NULL, " ");
    }
    if (i > 0) {
        result[i - 1] = '\0'; // Remove trailing space
    } else {
        result[0] = '\0';
    }

    return result;
}

int main() {
    char phrase1[] = "How can mirrors be real if our eyes aren't real";
    char *jaden_case1 = toJadenCase(phrase1);
    if (jaden_case1 != NULL) {
      printf("%s\n", jaden_case1);
      free(jaden_case1);
    }

    char phrase2[] = "most trees are blue";
    char *jaden_case2 = toJadenCase(phrase2);
    if (jaden_case2 != NULL) {
      printf("%s\n", jaden_case2);
      free(jaden_case2);
    }


    char *jaden_case3 = toJadenCase("");
    if(jaden_case3 != NULL) {
        printf("%s\n", jaden_case3);
        free(jaden_case3);
    }

    char *jaden_case4 = toJadenCase(NULL);
    if (jaden_case4 != NULL) {
      printf("%s\n", jaden_case4);
      free(jaden_case4);
    }
    
    char phrase5[] = "there is no spoon";
    char *jaden_case5 = toJadenCase(phrase5);
    if (jaden_case5 != NULL) {
      printf("%s\n", jaden_case5);
      free(jaden_case5);
    }


    return 0;
}