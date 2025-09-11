#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

bool isValidPassword(char *password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool upperCase = false;
    bool lowerCase = false;
    bool digit = false;
    bool specialChar = false;
    for (int i = 0; password[i]; i++) {
        char ch = password[i];
        if (isupper(ch)) upperCase = true;
        else if (islower(ch)) lowerCase = true;
        else if (isdigit(ch)) digit = true;
        else specialChar = true;
    }
    return upperCase && lowerCase && digit && specialChar;
}

int main() {
    printf("%d\n", isValidPassword("Admin123!"));  // 1 (true)
    printf("%d\n", isValidPassword("admin123!"));  // 0 (false, no uppercase)
    printf("%d\n", isValidPassword("ADMIN123!"));  // 0 (false, no lowercase)
    printf("%d\n", isValidPassword("Admin!Admin"));  // 0 (false, no digit)
    printf("%d\n", isValidPassword("Admin1234"));  // 0 (false, no special character)
    return 0;
}