
// C doesn't have built-in support for creating web APIs.\n// Would need to use external libraries like libmicrohttpd\n// Here's a basic structure of how it might look:

#include <microhttpd.h>
#include <string.h>
#include <stdio.h>

#define PORT 8080

struct User {
    char name[100];
    char email[100];
};

struct User users[100];
int user_count = 0;

static int handle_request(void *cls,
                        struct MHD_Connection *connection,
                        const char *url,
                        const char *method,
                        const char *version,
                        const char *upload_data,
                        size_t *upload_data_size,
                        void **con_cls) {
    
    if (strcmp(method, "POST") == 0 && strcmp(url, "/users") == 0) {
        // Handle POST request
        // Parse JSON and add user
        // This is simplified - actual implementation would need JSON parsing
    }
    else if (strcmp(method, "GET") == 0 && strcmp(url, "/users") == 0) {
        // Handle GET request
        // Return list of users as JSON
    }
    
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;
    
    daemon = MHD_start_daemon(MHD_USE_AUTO,
                            PORT,
                            NULL,
                            NULL,
                            &handle_request,
                            NULL,
                            MHD_OPTION_END);
                            
    if (daemon == NULL) {
        return 1;
    }
    
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}
