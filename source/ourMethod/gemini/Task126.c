#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to convert a string to lowercase
void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}


char* redirect(const char *input) {

 if (input == NULL)
 {
    return "Invalid Input";
 }

    char lowerInput[100]; 
    strcpy(lowerInput, input);
    toLower(lowerInput);

    if (strcmp(lowerInput, "home") == 0) {
        return "/home";
    } else if (strcmp(lowerInput, "profile") == 0) {
        return "/profile";
    } else if (strcmp(lowerInput, "settings") == 0) {
        return "/settings";
    } else {
        return "/error";
    }
}

int main() {
    char input1[100];
    printf("Enter your input: ");
    fgets(input1, sizeof(input1), stdin);

    // Remove the newline character from fgets
    input1[strcspn(input1, "\n")] = 0;

    printf("Redirect page for %s: %s\n", input1, redirect(input1));

    char *input2 = "profile";
    printf("Redirect page for %s: %s\n", input2, redirect(input2));

    char *input3 = "SETTINGS";
    printf("Redirect page for %s: %s\n", input3, redirect(input3));

    char *input4 = "invalid";
    printf("Redirect page for %s: %s\n", input4, redirect(input4));
    
    char *input5 = NULL;
    printf("Redirect page for %s: %s\n", "NULL", redirect(input5));


    return 0;
}