#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* redirect(char* user_input) {
    char* redirect_url = "";

    // Validate user input to prevent vulnerabilities
    if (user_input != NULL) {
        int valid = 1;
        for (int i = 0; user_input[i] != '\0'; i++) {
            if (!isalnum(user_input[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            if (strcmp(user_input, "home") == 0) {
                redirect_url = "/home";
            } else if (strcmp(user_input, "profile") == 0) {
                redirect_url = "/profile";
            } else if (strcmp(user_input, "settings") == 0) {
                redirect_url = "/settings";
            } else {
                redirect_url = "/error";
            }
        }
         else {
                redirect_url = "/error";
            }
    } else {
        redirect_url = "/error";
    }
    

    return redirect_url;
}

int main() {
    printf("%s\n", redirect("home"));
    printf("%s\n", redirect("profile"));
    printf("%s\n", redirect("settings"));
    printf("%s\n", redirect("invalid"));
    printf("%s\n", redirect("<script>alert('XSS')</script>"));
    return 0;
}