#include <onion/onion.h>
#include <onion/session.h>

void session_handler(void *priv, onion_request *req, onion_response *res) {
    onion_session_set(req, "user", "username");
    // Perform other operations
    onion_session_unset(req, "user"); // To terminate the session
    onion_response_printf(res, "Session managed");
}

int main() {
    onion *o = onion_new(O_THREADED);
    onion_url *url = onion_root_url(o);
    onion_url_add(url, "^$", session_handler);
    onion_listen(o);
    onion_free(o);
    return 0;
}