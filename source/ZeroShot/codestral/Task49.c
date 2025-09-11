// C with libmicrohttpd
// A complete implementation would be much more complex and beyond the scope of this example.
#include <microhttpd.h>

int post_handler(void *cls, struct MHD_Connection *connection,
                 const char *url, const char *method, const char *version,
                 const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (0 == strcmp(method, MHD_HTTP_METHOD_POST)) {
        // Save user to database
        return MHD_YES;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL, &post_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    (void) getchar();
    MHD_stop_daemon(daemon);
    return 0;
}