// C code to handle CSRF protection in a web application
#include <stdio.h>
#include <string.h>

const char* updateUserSettings(const char* csrfToken, const char* providedToken, const char* settings) {
    if (strcmp(csrfToken, providedToken) != 0) {
        return "CSRF token mismatch";
    }
    // Logic to update settings
    return "Settings updated successfully";
}

int main() {
    const char* csrfToken = "secureRandomToken";

    // Test cases
    printf("%s\n", updateUserSettings(csrfToken, "secureRandomToken", "newSettings")); // Should succeed
    printf("%s\n", updateUserSettings(csrfToken, "wrongToken", "newSettings")); // Should fail
    printf("%s\n", updateUserSettings(csrfToken, "secureRandomToken", "newSettings")); // Should succeed
    printf("%s\n", updateUserSettings(csrfToken, "wrongToken", "newSettings")); // Should fail
    printf("%s\n", updateUserSettings(csrfToken, "secureRandomToken", "newSettings")); // Should succeed

    return 0;
}