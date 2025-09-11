#include <stdio.h>
#include <string.h>

char* redirect(char* input) {
    if (strcmp(input, "home") == 0) {
        return "/home";
    } else if (strcmp(input, "about") == 0) {
        return "/about";
    } else if (strcmp(input, "contact") == 0) {
        return "/contact";
    } else {
        return "/404";
    }
}

int main() {
    printf("%s\n", redirect("home"));
    printf("%s\n", redirect("about"));
    printf("%s\n", redirect("contact"));
    printf("%s\n", redirect("blog"));
    printf("%s\n", redirect("products"));
    return 0;
}