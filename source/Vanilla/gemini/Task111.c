//  A simple XML-RPC server written in C.  This invokes functions
//  registered with the server.

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static xmlrpc_value *
sample_add(xmlrpc_env *   const envP,
            xmlrpc_value * const paramArrayP,
            void *         const serverInfo,
            void *         const channelInfo) {

    xmlrpc_int32 x, y, z;

    /* Parse our argument array. */
    xmlrpc_params_array_unpack(envP, paramArrayP, "(ii)", &x, &y);
    if (envP->fault_occurred)
        return NULL;

    z = x + y;

    /* Return our result. */
    return xmlrpc_build_value(envP, "i", z);
}

static xmlrpc_value *
sample_greet(xmlrpc_env *   const envP,
             xmlrpc_value * const paramArrayP,
             void *         const serverInfo,
             void *         const channelInfo) {

    char * name;
    char * greeting;
    size_t greetingSize;

    xmlrpc_params_array_unpack(envP, paramArrayP, "(s)", &name);

    if (envP->fault_occurred)
        return NULL;

    greetingSize = strlen("Hello, ") + strlen(name) + strlen("!") + 1;
    greeting = (char*) malloc(greetingSize);
    snprintf(greeting, greetingSize, "Hello, %s!", name);
    xmlrpc_DECREF(name); // Did this because xmlrpc_params_array_unpack doesn't

    xmlrpc_value * result = xmlrpc_build_value(envP, "s", greeting);
    free(greeting);

    return result;
}




int main(int           const argc,
         const char ** const argv) {

    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_server_abyss_t * serverP;
    xmlrpc_registry * registryP;
    xmlrpc_env env;

    if (argc-1 > 0) {
        fprintf(stderr, "This program has no arguments\n");
        exit(1);
    }

    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);
    if (env.fault_occurred) {
        fprintf(stderr, "xmlrpc_registry_new() failed.  %s\n", env.fault_string);
        exit(1);
    }

    xmlrpc_registry_add_method(
        &env, registryP, NULL, "ops.add", &sample_add, NULL);
    if (env.fault_occurred) {
        fprintf(stderr,"xmlrpc_registry_add_method(\"sample.add\") "
                "failed.  %s\n", env.fault_string);
        exit(1);
    }
     xmlrpc_registry_add_method(
        &env, registryP, NULL, "ops.greet", &sample_greet, NULL);

    if (env.fault_occurred) {
        fprintf(stderr,"xmlrpc_registry_add_method(\"sample.greet\") "
                "failed.  %s\n", env.fault_string);
        exit(1);
    }


    serverparm.config_file_p = NULL;
    serverparm.registry_p = registryP;
    serverparm.port_number = 8080;

    serverP = xmlrpc_server_abyss_new(&env, &serverparm);
    if (env.fault_occurred) {
        fprintf(stderr, "xmlrpc_server_abyss_new() failed.  %s\n",
                env.fault_string);
        exit(1);
    }

    printf("Running XML-RPC server...\n");


    xmlrpc_server_abyss_run(serverP);


    // Test Cases (Client-side code would typically handle these)
    // These are just demonstrations.  A real test would involve a client.

    // Test 1: add(5, 7)
    // Expected: 12

    // Test 2: greet("World")
    // Expected: "Hello, World!"

    // Test 3: add(-3, 10)
    // Expected: 7

    // Test 4: greet("XML-RPC")
    // Expected: "Hello, XML-RPC!"

    // Test 5: add(0, 0)
    // Expected: 0

    xmlrpc_server_abyss_destroy(serverP);

    xmlrpc_registry_free(registryP);

    xmlrpc_env_cleanup(&env);

    return 0;
}