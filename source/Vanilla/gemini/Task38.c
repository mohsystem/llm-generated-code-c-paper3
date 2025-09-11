#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (mg_vcmp(&hm->uri, "/") == 0) {
        char user_input[1024] = "";
        if (mg_vcmp(&hm->method, "POST") == 0) {
          mg_get_http_var(&hm->body, "userInput", user_input, sizeof(user_input));
        }
        
        struct mg_str html_header = mg_mk_str("HTTP/1.1 200 OK\r\n"
                                               "Content-Type: text/html\r\n\r\n");

        struct mg_str html_start = mg_mk_str("<html><body>");
        struct mg_str user_input_str = mg_mk_str(user_input);
        struct mg_str html_end = mg_mk_str("</body></html>");
        mg_printf(nc, "%.*s", (int) html_header.len, html_header.p);
        mg_printf(nc, "%.*s", (int) html_start.len, html_start.p);

        if (strlen(user_input)>0){
           mg_printf(nc, "<h1>You entered: %.*s</h1>", (int) user_input_str.len, user_input_str.p);
        }


        mg_printf(nc, "%.*s", (int) html_end.len, html_end.p);

        nc->flags |= MG_F_SEND_AND_CLOSE;
      }
      break;
    default:
      break;
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);
  mg_http_listen(&mgr, "http://localhost:8080", ev_handler, &mgr);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);
  return 0;
}