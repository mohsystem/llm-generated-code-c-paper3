// Note: libonion does not have built-in support for CORS.
// You would need to manually add the necessary headers to your responses.
// This is a simplified example of how you might handle a GET request.
int get_handler(void *data, onion_request *req, onion_response *res) {
    onion_response_write0(res, "HTTP/1.1 200 OK\r\n");
    onion_response_write0(res, "Access-Control-Allow-Origin: http://example.com\r\n");
    onion_response_write0(res, "Content-Type: application/json\r\n");
    onion_response_write0(res, "\r\n");
    onion_response_write0(res, "{\"data\": \"some data\"}");
    return OCS_PROCESSED;
}