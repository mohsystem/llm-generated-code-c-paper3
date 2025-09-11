#include <stdio.h>
#include <string.h>
#include <ldap.h>

// Function to search for a user in LDAP
char **searchUser(const char *domainComponent, const char *username) {
    LDAP *ld;
    int rc;
    char **results = NULL;

    // Initialize LDAP connection (secure with SSL)
    if (ldap_initialize(&ld, "ldaps://localhost:636") != LDAP_SUCCESS) { // ldaps for SSL
        fprintf(stderr, "ldap_init failed\n");
        return NULL;
    }

    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, 3);


    if(ldap_start_tls_s(ld, NULL, NULL) != LDAP_SUCCESS){
        fprintf(stderr, "ldap_start_tls_s failed\n");
        ldap_unbind_ext_s(ld, NULL, NULL); // Always unbind
        return NULL;
    }

    // Bind to the server (anonymous or provide credentials)
     rc = ldap_simple_bind_s(ld, NULL, NULL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_simple_bind_s: %s\n", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return NULL;
    }


    char baseDN[256];
    strcpy(baseDN, "dc=");
    strcat(baseDN, domainComponent);

    char *token = strtok(baseDN, ".");
    while (token != NULL) {
        strcat(baseDN, ",dc=");
        strcat(baseDN, token);
        token = strtok(NULL, ".");
    }

    char searchFilter[256];
    snprintf(searchFilter, sizeof(searchFilter), "(sAMAccountName=%s)", username);

    LDAPMessage *searchResult;
    rc = ldap_search_ext_s(ld, baseDN, LDAP_SCOPE_SUBTREE, searchFilter, NULL, 0, NULL, NULL, NULL/*LDAP_NO_LIMIT*/, LDAP_NO_LIMIT, &searchResult);

    if (rc == LDAP_SUCCESS) {
        int numEntries = ldap_count_entries(ld, searchResult);
        if (numEntries > 0) {
            LDAPMessage *entry;
            for (entry = ldap_first_entry(ld, searchResult); entry != NULL; entry = ldap_next_entry(ld, entry)) {
                BerElement *ber;
                char *attribute;
                for (attribute = ldap_first_attribute(ld, entry, &ber); attribute != NULL; attribute = ldap_next_attribute(ld, entry, ber)) {
                    char **vals;
                    if ((vals = ldap_get_values(ld, entry, attribute)) != NULL) {
                        results = vals; // Store the last set of values for simplicity
                        //  In a real application, you'd want to handle multiple attributes
                    }
                    ldap_memfree(attribute);
                }
                if (ber) ber_free(ber);
            }
        }
    }


    if(searchResult) ldap_msgfree(searchResult);

    ldap_unbind_ext_s(ld, NULL, NULL);
    return results;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <domainComponent> <username>\n", argv[0]);
        return 1;
    }

    char *domainComponent = argv[1];
    char *username = argv[2];


    char **result = searchUser(domainComponent, username);
    if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
        }
        ldap_value_free(result);
    }


    // Test Cases (Uncommented - they would require setting up corresponding users in your LDAP server)
    //searchUser("example.com", "testuser2");
    //searchUser("example.net", "testuser3");
    //searchUser("example.org", "testuser4");
    //searchUser("example.com", "testuser5");

    return 0;
}