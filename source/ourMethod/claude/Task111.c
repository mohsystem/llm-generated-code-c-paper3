
#include <xmlrpc.h>
#include <xmlrpc_server.h>
#include <xmlrpc_server_abyss.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PORT 8080
#define REGISTRY_ERROR -1

struct Task111 {
    xmlrpc_env env;
    xmlrpc_server_abyss_t* server;
};

// Calculator methods
static xmlrpc_value* add(xmlrpc_env* env, xmlrpc_value* param_array, void* user_data) {
    int x, y;
    
    // Extract parameters
    xmlrpc_decompose_value(env, param_array, "(ii)", &x, &y);
    if (env->fault_occurred)
        return NULL;
        
    // Input validation
    if (x > INT_MAX || x < INT_MIN || y > INT_MAX || y < INT_MIN) {
        xmlrpc_env_set_fault(env, REGISTRY_ERROR, "Input values out of range");
        return NULL;
    }
    
    // Check for overflow
    if ((y > 0 && x > INT_MAX - y) || (y < 0 && x < INT_MIN - y)) {
        xmlrpc_env_set_fault(env, REGISTRY_ERROR, "Addition would cause overflow");
        return NULL;
    }
    
    return xmlrpc_build_value(env, "i", x + y);
}

static xmlrpc_value* subtract(xmlrpc_env* env, xmlrpc_value* param_array, void* user_data) {
    int x, y;
    
    // Extract parameters
    xmlrpc_decompose_value(env, param_array, "(ii)", &x, &y);
    if (env->fault_occurred)
        return NULL;
        
    // Input validation
    if (x > INT_MAX || x < INT_MIN || y > INT_MAX || y < INT_MIN) {
        xmlrpc_env_set_fault(env, REGISTRY_ERROR, "Input values out of range");
        return NULL;
    }
    
    // Check for overflow
    if ((y < 0 && x > INT_MAX + y) || (y > 0 && x < INT_MIN + y)) {
        xmlrpc_env_set_fault(env, REGISTRY_ERROR, "Subtraction would cause overflow");
        return NULL;
    }
    
    return xmlrpc_build_value(env, "i", x - y);
}

static void test_calculator(void) {
    xmlrpc_env env;
    xmlrpc_env_init(&env);
    
    // Test cases
    printf("Test 1: 5 + 3 = ");
    xmlrpc_value* result1 = add(&env, xmlrpc_build_value(&env, "(ii)", 5, 3), NULL);
    if (!env.fault_occurred) {
        int val;
        xmlrpc_read_int(&env, result1, &val);
        printf("%d\\n", val);
    }
    
    printf("Test 2: 10 - 4 = ");
    xmlrpc_value* result2 = subtract(&env, xmlrpc_build_value(&env, "(ii)", 10, 4), NULL);
    if (!env.fault_occurred) {
        int val;
        xmlrpc_read_int(&env, result2, &val);
        printf("%d\\n", val);
    }
    
    printf("Test 3: -5 + 8 = ");
    xmlrpc_value* result3 = add(&env, xmlrpc_build_value(&env, "(ii)", -5, 8), NULL);
    if (!env.fault_occurred) {
        int val;
        xmlrpc_read_int(&env, result3, &val);
        printf("%d\\n", val);
    }
    
    printf("Test 4: 15 - (-5) = ");
    xmlrpc_value* result4 = subtract(&env, xmlrpc_build_value(&env, "(ii)", 15, -5), NULL);
    if (!env.fault_occurred) {
        int val;
        xmlrpc_read_int(&env, result4, &val);
        printf("%d\\n", val);
    }
    
    printf("Test 5: Invalid input test\\n");
    xmlrpc_value* result5 = add(&env, xmlrpc_build_value(&env, "(ii)", INT_MAX, 1), NULL);
    if (env.fault_occurred) {
        printf("Test 5 passed: %s\\n", env.fault_string);
    }
    
    xmlrpc_env_clean(&env);
}

int main(void) {
    struct Task111 server;
    xmlrpc_server_abyss_parms serverparm;
    
    // Initialize XML-RPC
    xmlrpc_', type='text')