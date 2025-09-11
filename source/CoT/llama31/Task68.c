#include <ldap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract_and_search(const char* username, const char* domain) {
    // Extract dc components from domain
    char* dcComponent1 = strtok((char*)domain, ".");
    char* dcComponent2 = strtok(nullptr, ".");

    // Construct LDAP query
    char ldapQuery[256];
    sprintf(ldapQuery, "uid=%s,dc=%s,dc=%s", username, dcComponent1, dcComponent2);

    // Establish LDAP connection and search
    LDAP* ld;
    int rc = ldap_initialize(&ld, "ldap://localhost:389");
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "LDAP initialization failed: %s\n", ldap_err2string(rc));
        return;
    }

    LDAPMessage* msg;
    rc = ldap_search_s(ld, ldapQuery, LDAP_SCOPE_SUBTREE, "(objectClass=*)", nullptr, 0, &msg);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "LDAP search failed: %s\n", ldap_err2string(rc));
        ldap_unbind_s(ld);
        return;
    }

    for (LDAPMessage* entry = ldap_first_entry(ld, msg); entry != nullptr; entry = ldap_next_entry(ld, entry)) {
        BerElement* ber;
        char* attr;
        for (attr = ldap_first_attribute(ld, entry, &ber); attr != nullptr; attr = ldap_next_attribute(ld, entry, ber)) {
            printf("User Information:\n");
            if (ldap_get_values_len(ld, entry, attr) != nullptr) {
                for (char** vals = ldap_get_values_len(ld, entry, attr); *vals != nullptr; vals++) {
                    printf("%s: %s\n", attr, *vals);
                }
                ldap_value_free_len(ldap_get_values_len(ld, entry, attr));
            }
            ldap_memfree(attr);
        }
        if (ber != nullptr) {
            ber_free(ber, 0);
        }
    }

    ldap_msgfree(msg);
    ldap_unbind_s(ld);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./Task68 <username> <domain>\n");
        return 1;
    }

    extract_and_search(argv[1], argv[2]);
    return 0;
}