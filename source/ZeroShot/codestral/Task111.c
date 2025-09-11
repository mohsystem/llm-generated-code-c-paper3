// C does not have a built-in XML-RPC library, so you'll need to use a third-party library like libxmlrpc.
// This example uses the libxmlrpc library.

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server_abyss.h>

static xmlrpc_value* add(xmlrpc_env* const envP, xmlrpc_value* const paramArrayP, void* const serverInfo, void* const userData) {
    int a, b;
    if (xmlrpc_get_int(envP, xmlrpc_array_item(paramArrayP, 0, NULL), &a) && xmlrpc_get_int(envP, xmlrpc_array_item(paramArrayP, 1, NULL), &b)) {
        return xmlrpc_build_value(envP, "i", a + b);
    }
    return NULL;
}

int main() {
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry* registryP;
    xmlrpc_env env;

    xmlrpc_env_init(&env);
    registryP = xmlrpc_registry_new(&env);

    xmlrpc_registry_add_method(&env, registryP, NULL, "Task111.add", add, NULL);

    serverparm.config_file_name = NULL;
    serverparm.registryP = registryP;
    serverparm.port_number = 8080;
    serverparm.log_file_name = "/tmp/xmlrpc_log";

    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));

    xmlrpc_env_clean(&env);
    return 0;
}