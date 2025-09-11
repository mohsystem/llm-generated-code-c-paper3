// Note: libonion is a third-party library. This example assumes that you have it installed.

#include <onion/onion.h>
#include <onion/log.h>
#include <onion/request.h>
#include <onion/response.h>

int input_handler(void *_, onion_request *req, onion_response *res) {
    onion_response_printf(res, "<form method='POST' action='/output'><input type='text' name='userInput'><input type='submit' value='Submit'></form>");
    return OCS_PROCESSED;
}

int output_handler(void *_, onion_request *req, onion_response *res) {
    const char *userInput = onion_request_get_post(req, "userInput");
    onion_response_printf(res, "<p>You entered: %s</p>", userInput);
    return OCS_PROCESSED;
}

int main() {
    onion *onion = onion_new(O_THR);
    onion_url *url;

    url = onion_root_url(onion);
    onion_url_add(url, "", input_handler, NULL);
    onion_url_add(url, "output", output_handler, NULL);

    onion_listen(onion, "localhost", 8080);
    onion_free(onion);
    return 0;
}