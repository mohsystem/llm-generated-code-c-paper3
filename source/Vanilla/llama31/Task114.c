#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char accessCharByIndex(char* s, int k) {
    return s[k];
}

char* insertString(char* s, char* ch, int k) {
    int len_s = strlen(s);
    int len_ch = strlen(ch);
    char* result = (char*)malloc(len_s + len_ch + 1);
    strncpy(result, s, k);
    result[k] = '\0';
    strcat(result, ch);
    strcat(result, s + k);
    return result;
}

char* modifyChar(char* s, int k, char ch) {
    s[k] = ch;
    return s;
}

char* concatenateString(char* s, char* ch) {
    int len_s = strlen(s);
    int len_ch = strlen(ch);
    char* result = (char*)malloc(len_s + len_ch + 1);
    strcpy(result, s);
    strcat(result, ch);
    return result;
}

int main() {
    // Test cases
    char s[] = "GeeksforGeeks";
    printf("Original String: %s\n", s);
    printf("Character at index 4: %c\n", accessCharByIndex(s, 4));
    char* inserted = insertString(s, "for", 5);
    printf("String after inserting 'for' at index 5: %s\n", inserted);
    free(inserted);
    char* modified = modifyChar(s, 6, 'F');
    printf("String after modifying character at index 6: %s\n", modified);
    char* concatenated = concatenateString(s, " is great");
    printf("String after concatenating ' is great': %s\n", concatenated);
    free(concatenated);
    return 0;
}