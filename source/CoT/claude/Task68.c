
#include <stdio.h>
#include <string.h>
#include <ldap.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RESULT_SIZE 2048
#define TIMEOUT_SECONDS 5

// Function to sanitize input
void sanitize_input(const char* input, char* output) {
    int j = 0;
    for(int i = 0; input[i] != '\\0'; i++) {
        if(isalnum(input[i]) || input[i] == '.') {
            output[j++] = input[i];
        }
    }
    output[j] = '\\0';
}

char* search_ldap(const char* username, const char* domain) {
    if(!username || !domain || !strlen(username) || !strlen(domain)) {
        return strdup("Invalid input parameters");
    }

    char sanitized_username[256] = {0};
    char sanitized_domain[256] = {0};
    char* result = malloc(MAX_RESULT_SIZE);
    if(!result) return NULL;
    result[0] = '\\0';

    // Sanitize inputs
    sanitize_input(username, sanitized_username);
    sanitize_input(domain, sanitized_domain);

    LDAP* ld = NULL;
    int rc;

    // Initialize LDAP connection
    rc = ldap_initialize(&ld, "ldap://localhost:389");
    if(rc != LDAP_SUCCESS) {
        snprintf(result, MAX_RESULT_SIZE, "Failed to initialize LDAP: %s", ldap_err2string(rc));
        return result;
    }

    // Set LDAP version
    int version = LDAP_VERSION3;
    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    // Set timeout
    struct timeval timeout = {TIMEOUT_SECONDS, 0};
    ldap_set_option(ld, LDAP_OPT_TIMEOUT, &timeout);

    // Construct search base
    char search_base[512] = {0};
    char* domain_copy = strdup(sanitized_domain);
    char* token = strtok(domain_copy, ".");
    int offset = 0;
    
    while(token) {
        offset += snprintf(search_base + offset, sizeof(search_base) - offset, 
                         offset == 0 ? "dc=%s" : ",dc=%s", token);
        token = strtok(NULL, ".");
    }
    free(domain_copy);

    // Construct search filter
    char search_filter[512];
    snprintf(search_filter, sizeof(search_filter), 
             "(&(objectClass=person)(uid=%s))", sanitized_username);

    // Perform search
    LDAPMessage* res = NULL;
    char* attrs[] = {"*", NULL};
    
    rc = ldap_search_ext_s(
        ld,
        search_base,
        LDAP_SCOPE_SUBTREE,
        search_filter,
        attrs,
        0,
        NULL,
        NULL,
        &timeout,
        0,
        &res
    );

    if(rc != LDAP_SUCCESS) {
        snprintf(result, MAX_RESULT_SIZE, "LDAP search failed: %s", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return result;
    }

    int entry_count = ldap_count_entries(ld, res);
    if(entry_count == 0) {
        strcpy(result, "No results found");
    } else {
        // Process results
        LDAPMessage* entry;
        char* dn;
        int result_offset = 0;

        for(entry = ldap_first_entry(ld, res); 
            entry != NULL; 
            entry = ldap_next_entry(ld, entry)) {
            
            dn = ldap_get_dn(ld, entry);
            result_offset += snprintf(result + result_offset, 
                                    MAX_RESULT_SIZE - result_offset,
                                    "DN: %s\\n", dn);
            ldap_memfree(dn);

            BerElement* ber;
            char* attr;
            
            for(attr = ldap_first_attribute(ld, entry, &ber);
                attr != NULL;
                attr = ldap_next_attribute(ld, entry, ber)) {
                
                struct berval** vals = ldap_get_values_len(ld, entry, attr);
                if(vals != NULL) {
                    result_offset += snprintf(result + result_offset,
                                           MAX_RESULT_SIZE - result_offset,
                                           "%s: %.*s\\n", 
                                           attr,
                                           (int)vals[0]->bv_len,
                                           vals[0]->bv_val);
                    ldap_value_free_len(vals);
                }
                ldap_memfree(attr);
            }
            
            if(ber != NULL) {
                ber_free(ber, 0);
            }
        }
    }

    ldap_msgfree(res);
    ldap_unbin', type='text')