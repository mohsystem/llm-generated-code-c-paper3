// Pseudo-code for generating and verifying CSRF tokens
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

// ...

const char *generate_csrf_token()
{
    char *token = malloc(33);
    for (int i = 0; i < 32; i++)
        token[i] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 62];
    token[32] = '\0';
    return token;
}

int is_csrf_token_valid(struct MHD_Connection *connection, const char *session_token)
{
    const char *request_token;
    MHD_get_connection_value(connection, MHD_GET_ARGUMENT_KIND, "csrf_token", &request_token);
    return request_token != NULL && strcmp(request_token, session_token) == 0;
}