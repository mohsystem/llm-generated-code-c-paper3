// C language does not have built-in support for CORS.
// It is recommended to use a library or framework that provides this functionality.
// This example assumes that you are using the libonion library.

#include <onion/onion.h>
#include <onion/response.h>
#include <onion/request.h>
#include <onion/log.h>

static void handle_api(void* _req, void* _res) {
    onion_request* req = _req;
    onion_response* res = _res;

    onion_response_set_header(res, "Access-Control-Allow-Origin", "http://example.com");
    onion_response_printf(res, "API response");
}

int main() {
    onion* o = onion_new(O_ONE_LOOP);
    onion_url* url = onion_root_url(o);
    onion_url_add(url, "api", handle_api);
    onion_listen(o, "0.0.0.0", 8080);
    onion_free(o);
    return 0;
}