#include <stdio.h>
#include <ldap.h>

void searchLDAP(const char* username, const char* domain) {
    LDAP* ld;
    int rc;
    LDAPMessage* msg;
    LDAPMessage* entry;
    BerElement* ber;

    // Initialize LDAP
    if ((ld = ldap_init("localhost", 389)) == NULL) {
        perror("ldap_init");
        return;
    }

    // Set LDAP version
    int version = LDAP_VERSION3;
    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    // Bind anonymously
    rc = ldap_simple_bind_s(ld, NULL, NULL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_simple_bind_s: %s\n", ldap_err2string(rc));
        ldap_unbind_s(ld);
        return;
    }

    // Construct search base and filter
    char baseDN[256];
    sprintf(baseDN, "dc=%s", domain);
    for (char* c = baseDN; *c; ++c) {
        if (*c == '.') {
            *c = ',';
            sprintf(c + 1, "dc=%s", c + 2);
        }
    }
    char filter[256];
    sprintf(filter, "(uid=%s)", username);

    // Search
    rc = ldap_search_ext_s(ld, baseDN, LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, NULL, NULL, 0, &msg);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_search_ext_s: %s\n", ldap_err2string(rc));
        ldap_unbind_s(ld);
        return;
    }

    // Print results
    for (entry = ldap_first_entry(ld, msg); entry != NULL; entry = ldap_next_entry(ld, entry)) {
        for (ber = ldap_first_attribute(ld, entry, NULL); ber != NULL; ber = ldap_next_attribute(ld, entry, ber)) {
            char* attr = ldap_get_dn(ld, entry);
            printf("%s\n", attr);
            ldap_memfree(attr);
            char** vals;
            if ((vals = ldap_get_values_len(ld, entry, ber)) != NULL) {
                for (int i = 0; vals[i] != NULL; ++i) {
                    printf("%s: %s\n", ldap_get_attribute_type(ber), vals[i]);
                }
                ldap_value_free_len(vals);
            }
            ldap_memfree(ber);
        }
    }

    ldap_msgfree(msg);
    ldap_unbind_s(ld);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: ./Task68 <username> <domain>\n");
        return 1;
    }

    searchLDAP(argv[1], argv[2]);
    return 0;
}