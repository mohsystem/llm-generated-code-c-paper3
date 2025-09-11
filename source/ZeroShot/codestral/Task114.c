#include<stdio.h>
#include<string.h>

void copy_string(char *str1, char *str3) {
    // Copying a string
    strcpy(str3, str1);
    printf("Copied string: %s\n", str3);
}

void concatenate_strings(char *str1, char *str2, char *str4) {
    // Concatenating two strings
    strcpy(str4, str1);
    strcat(str4, str2);
    printf("Concatenated string: %s\n", str4);
}

void manipulate_string(char *str1, char *str5) {
    // Manipulating a string
    strcpy(str5, str1);
    for (int i = 0; str5[i]; i++)
        if (str5[i] == 'l')
            str5[i] = 'm';
    printf("Manipulated string: %s\n", str5);
}

int main() {
    char str1[] = "Hello";
    char str2[] = " World";
    char str3[20], str4[30], str5[20];

    copy_string(str1, str3);
    concatenate_strings(str1, str2, str4);
    manipulate_string(str1, str5);

    return 0;
}