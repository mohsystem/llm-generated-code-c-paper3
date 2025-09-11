#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

int main() {
    // Generate CSRF token
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    char csrfToken[37];
    uuid_unparse(bin_uuid, csrfToken);

    // Simulate HTTP request handling
    char* requestMethod = getenv("REQUEST_METHOD");
    char* csrfTokenFromRequest = getenv("csrf_token");
    char* username = getenv("username");
    char* email = getenv("email");

    // In a real CGI application, you would parse these from the request
    // For simplicity, assume we have them
    if (strcmp(requestMethod, "POST") == 0) {
        if (strcmp(csrfTokenFromRequest, csrfToken) != 0) {
            printf("Invalid CSRF token\n");
            return 1;
        }

        // Update user settings
        // Assuming you have functions to update user settings
        updateUserSettings(username, email);
    }

    // Output HTML form
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/updateUser\" method=\"post\">");
    printf("<input type=\"hidden\" name=\"csrf_token\" value=\"%s\">", csrfToken);
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"email\">Email:</label>");
    printf("<input type=\"email\" id=\"email\" name=\"email\"><br><br>");
    printf("<input type=\"submit\" value=\"Update\">");
    printf("</form></body></html>");

    return 0;
}