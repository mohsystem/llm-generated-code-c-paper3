
// C equivalent using LDAP as JNDI is Java-specific
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ldap.h>

#define MAX_RESOURCE_NAME 256
#define LDAP_SERVER "ldap://localhost:389"

typedef struct {
    LDAP* ld;
} Task107;

// Function to validate resource name
int is_valid_resource_name(const char* name) {
    if (!name || !*name || !isalpha(*name)) {
        return 0;
    }
    
    while (*name) {
        if (!isalnum(*name) && *name != '_' && *name != '/' && 
            *name != '.' && *name != '-') {
            return 0;
        }
        name++;
    }
    return 1;
}

// Initialize LDAP connection
Task107* init_task107(void) {
    Task107* task = (Task107*)malloc(sizeof(Task107));
    if (!task) {
        return NULL;
    }

    int rc = ldap_initialize(&task->ld, LDAP_SERVER);
    if (rc != LDAP_SUCCESS) {
        free(task);
        return NULL;
    }

    // Set LDAP protocol version
    int version = LDAP_VERSION3;
    ldap_set_option(task->ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    return task;
}

// Cleanup LDAP connection
void cleanup_task107(Task107* task) {
    if (task) {
        if (task->ld) {
            ldap_unbind_ext(task->ld, NULL, NULL);
        }
        free(task);
    }
}

// Lookup resource in LDAP
char* lookup_resource(Task107* task, const char* resource_name) {
    if (!task || !resource_name || strlen(resource_name) >= MAX_RESOURCE_NAME) {
        return NULL;
    }

    if (!is_valid_resource_name(resource_name)) {
        return NULL;
    }

    LDAPMessage* result = NULL;
    char* attrs[] = { "objectClass", NULL };
    
    int rc = ldap_search_ext_s(
        task->ld, resource_name, LDAP_SCOPE_BASE,
        "(objectClass=*)", attrs, 0,
        NULL, NULL, NULL, 0, &result);

    char* return_value = NULL;
    
    if (rc == LDAP_SUCCESS && result) {
        char* attr;
        BerElement* ber;
        char** values;

        for (attr = ldap_first_attribute(task->ld, result, &ber);
             attr != NULL;
             attr = ldap_next_attribute(task->ld, result, ber)) {
            
            values = ldap_get_values(task->ld, result, attr);
            if (values) {
                return_value = strdup(values[0]);
                ldap_value_free(values);
                ldap_memfree(attr);
                break;
            }
            ldap_memfree(attr);
        }

        if (ber) {
            ber_free(ber, 0);
        }
    }

    if (result) {
        ldap_msgfree(result);
    }

    return return_value;
}

int main() {
    Task107* service = init_task107();
    if (!service) {
        fprintf(stderr, "Failed to initialize service\\n");
        return 1;
    }

    // Test cases
    const char* test_cases[] = {
        "dc=example,dc=com",
        "ou=users,dc=example,dc=com",
        "cn=admin,dc=example,dc=com",
        "ou=groups,dc=example,dc=com",
        "cn=testuser,ou=users,dc=example,dc=com"
    };

    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        printf("Looking up: %s\\n", test_cases[i]);
        char* result = lookup_resource(service, test_cases[i]);
        if (result) {
            printf("Result: %s\\n", result);
            free(result);
        } else {
            printf("Error looking up %s\\n", test_cases[i]);
        }
    }

    cleanup_task107(service);
    return 0;
}
