#include <stdio.h>
#include <microhttpd.h>

#define PORT 8888

int send_response(struct MHD_Connection *connection, const char *content) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(content), (void*) content, MHD_RESPMEM_PERSISTENT);
    MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");
    MHD_add_response_header(response, "Access-Control-Allow-Methods", "GET, POST, DELETE, PUT");
    MHD_add_response_header(response, "Access-Control-Allow-Headers", "Content-Type");

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, 
                         const char *url, const char *method, const char *version, 
                         const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (0 == strcmp(method, "GET")) {
        return send_response(connection, "{\"message\": \"CORS is working!\"}");
    }
    return MHD_NO; // Method not allowed
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, 
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar(); // Wait for a key press
    MHD_stop_daemon(daemon);
    return 0;
}