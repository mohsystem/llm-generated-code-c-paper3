// This example is highly simplified and not practical for real-world use.
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static void event_handler(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        if (mg_vcmp(&hm->method, "GET") == 0) {
            mg_send_head(c, 200, mg_calc_content_len("text/html", 0),
                         "Content-Type: text/html\r\n\r\n"
                         "<form action='/updateUser' method='post'>"
                         "<input type='hidden' name='csrfToken' value='valid_token'>"
                         "<input type='text' name='username' placeholder='Username'>"
                         "<input type='email' name='email' placeholder='Email'>"
                         "<input type='submit' value='Update'>"
                         "</form>");
        } else if (mg_vcmp(&hm->method, "POST") == 0) {
            char csrfToken[100], username[100], email[100];
            mg_get_http_var(&hm->body, "csrfToken", csrfToken, sizeof(csrfToken));
            mg_get_http_var(&hm->body, "username", username, sizeof(username));
            mg_get_http_var(&hm->body, "email", email, sizeof(email));

            if (strcmp(csrfToken, "valid_token") != 0) {
                mg_send_head(c, 400, mg_calc_content_len("text/plain", 0),
                            "Content-Type: text/plain\r\n\r\nCSRF token is invalid");
            } else {
                printf("Updating user settings for %s with email %s\n", username, email);
                mg_send_head(c, 200, mg_calc_content_len("text/plain", 0),
                             "Content-Type: text/plain\r\n\r\nUser settings updated successfully");
            }
        }
    }
}

int main() {
    struct mg_server *server = mg_create_server(NULL, event_handler);
    mg_set_option(server, "listening_port", "8080");
    mg_start(server);
    while (1) {
        mg_poll_server(server, 1000);
    }
    mg_destroy_server(&server);
    return 0;
}