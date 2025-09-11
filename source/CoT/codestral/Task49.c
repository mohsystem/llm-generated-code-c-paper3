// Creating an HTTP server in C is a complex task and generally not recommended. This example uses libmicrohttpd for simplicity, but it is still a simplification and does not include error handling or input validation.

#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888
#define MAX_USERS 100

struct User {
    char id[20];
    char name[20];
};

struct User users[MAX_USERS];
int user_count = 0;

int handle_post(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "POST"))
        return MHD_NO;

    if (0 != strcmp(url, "/users"))
        return MHD_NO;

    if (user_count >= MAX_USERS)
        return MHD_NO;

    struct User *user = &users[user_count++];
    sscanf(upload_data, "{\"id\":\"%[^\"]\",\"name\":\"%[^\"]\"}", user->id, user->name);

    *upload_data_size = 0;
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &handle_post, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    (void) getchar();

    MHD_stop_daemon(daemon);
    return 0;
}