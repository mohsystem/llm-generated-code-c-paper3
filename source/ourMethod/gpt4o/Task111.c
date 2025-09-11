#include <stdio.h>
#include <stdlib.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

static xmlrpc_value * sum(xmlrpc_env *   const envP, 
                          xmlrpc_value * const paramArrayP, 
                          void *         const serverInfo,
                          void *         const channelInfo) {
    xmlrpc_int32 x, y;
    xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &x, &y);
    return xmlrpc_build_value(envP, "i", x + y);
}

int main(int argc, const char **argv) {
    struct xmlrpc_method_info3 const sum_method = {
        .methodName     = "Task111.sum",
        .methodFunction = &sum,
    };

    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;

    xmlrpc_env env;
    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);
    xmlrpc_registry_add_method3(&env, registryP, &sum_method);

    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = 8080;

    printf("Starting XML-RPC server on port 8080...\n");
    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(port_number));

    xmlrpc_env_clean(&env);
    xmlrpc_registry_free(registryP);

    return 0;
}