#include <stdio.h>
#include <string.h>

void display_on_web(char *user_input) {
    printf("<html><body><p>%s</p></body></html>\n", user_input);
}

int main() {
    char user_input[100];
    printf("Please enter your input: ");
    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = 0;
    display_on_web(user_input);
    return 0;
}