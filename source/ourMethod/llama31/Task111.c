#include <libxmlrpc/xmlrpc.h>
#include <libxmlrpc/xmlrpc_server.h>
#include <libxmlrpc/xmlrpc_client.h>

void my_mul(xmlrpc_env *envP, xmlrpc_value *paramArrayP, xmlrpc_value *resultP) {
    int x, y;
    xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &x, &y);
    xmlrpc_int64_t result = x * y;
    xmlrpc_make_int64(envP, result, resultP);
}

void my_add(xmlrpc_env *envP, xmlrpc_value *paramArrayP, xmlrpc_value *resultP) {
    int x, y;
    xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &x, &y);
    xmlrpc_int64_t result = x + y;
    xmlrpc_make_int64(envP, result, resultP);
}

void my_greet(xmlrpc_env *envP, xmlrpc_value *paramArrayP, xmlrpc_value *resultP) {
    const char *name;
    xmlrpc_decompose_value(envP, paramArrayP, "(s)", &name);
    char *greeting = malloc(strlen(name) + 10);
    sprintf(greeting, "Hello, %s!", name);
    xmlrpc_make_string(envP, greeting, resultP);
    free(greeting);
}

int main() {
    xmlrpc_env env;
    xmlrpc_server_info_t server_info;

    // Initialize the environment
    xmlrpc_env_init(&env);

    // Set up the server
    server_info.port = 8080;
    server_info.path = "/RPC2";

    // Register methods
    xmlrpc_registry_add_method2(&server_info.registryP, "sample.mul", my_mul);
    xmlrpc_registry_add_method2(&server_info.registryP, "sample.add", my_add);
    xmlrpc_registry_add_method2(&server_info.registryP, "sample.greet", my_greet);

    // Start the server
    xmlrpc_server_run(&server_info);

    return 0;
}