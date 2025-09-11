// Assuming libmicrohttpd library is available

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PAGE "<html><body><p>User Input: %s</p></body></html>"

int display_input(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **ptr) {
    static int dummy;
    const char *user_input;
    char *safe_input;
    char *response;
    size_t response_size;
    struct MHD_Response *mhd_response;
    int ret;

    if (0 != strcmp(method, MHD_HTTP_METHOD_GET))
        return MHD_NO;

    user_input = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "userInput");
    if (user_input == NULL)
        user_input = "";

    safe_input = malloc(strlen(user_input) * 6 + 1); // Allocate sufficient memory for escaped input
    if (safe_input == NULL)
        return MHD_NO;

    html_escape(safe_input, user_input, strlen(user_input)); // Assume a function to escape HTML entities

    response_size = snprintf(NULL, 0, PAGE, safe_input) + 1;
    response = malloc(response_size);
    if (response == NULL) {
        free(safe_input);
        return MHD_NO;
    }

    snprintf(response, response_size, PAGE, safe_input);

    mhd_response = MHD_create_response_from_buffer(response_size, response, MHD_RESPMEM_MUST_FREE);
    if (mhd_response == NULL) {
        free(safe_input);
        free(response);
        return MHD_NO;
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    free(safe_input);

    return ret;
}

int main() {
    // Initialize the server and handle HTTP requests
    // Register display_input function to handle requests to the root path
}