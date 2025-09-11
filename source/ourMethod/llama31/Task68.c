#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ldap.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <username> <domain>\n", argv[0]);
        return 1;
    }

    char* username = argv[1];
    char* domain = argv[2];

    // Validate inputs to prevent injection attacks
    if (strchr(username, '*') || strchr(username, '(') || strchr(username, ')')) {
        printf("Invalid username\n");
        return 1;
    }
    if (strchr(domain, '*') || strchr(domain, '(') || strchr(domain, ')')) {
        printf("Invalid domain\n");
        return 1;
    }

    // Construct LDAP query
    char ldapQuery[256];
    sprintf(ldapQuery, "(&(objectClass=user)(sAMAccountName=%s)(dc=%s))", username, domain);

    // Initialize LDAP
    LDAP* ld;
    int rc = ldap_initialize(&ld, "ldap://localhost:389");
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "LDAP initialization failed: %s\n", ldap_err2string(rc));
        return 1;
    }

    // Bind to LDAP server
    const char* bindDN = "cn=admin,dc=example,dc=com"; // Replace with actual bind DN
    const char* bindPW = "password"; // Replace with actual password
    rc = ldap_bind_s(ld, bindDN, bindPW, LDAP_AUTH_SIMPLE);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "LDAP bind failed: %s\n", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return 1;
    }

    // Search for user
    LDAPMessage* msg;
    rc = ldap_search_ext_s(ld, (char*)("dc=" + domain), LDAP_SCOPE_SUBTREE, ldapQuery, NULL, 0, NULL, NULL, NULL, 0, &msg);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "LDAP search failed: %s\n", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return 1;
    }

    // Process search results
    BerElement* ber;
    char* attr;
    int num_entries = ldap_count_entries(ld, msg);
    for (int i = 0; i < num_entries; ++i) {
        LDAPMessage* entry = ldap_first_entry(ld, msg);
        while (entry != NULL) {
            BerElement* ber;
            char* attr;
            if ((attr = ldap_get_dn(ld, entry)) != NULL) {
                printf("User found: %s\n", attr);
                ldap_memfree(attr);
            }
            entry = ldap_next_entry(ld, entry);
        }
    }

    // Unbind from LDAP server
    ldap_msgfree(msg);
    ldap_unbind_ext_s(ld, NULL, NULL);

    return 0;
}