#include <stdio.h>
#include <ldap.h>
#include <string.h>

char* escapeLDAPSearchFilter(const char* filter) {
    size_t filterLen = strlen(filter);
    char* escaped = malloc(filterLen * 2 + 1);
    char* ptr = escaped;

    for (size_t i = 0; i < filterLen; ++i) {
        switch (filter[i]) {
            case '\\':
                *ptr++ = '\\';
                *ptr++ = '5';
                *ptr++ = 'c';
                break;
            case '*':
                *ptr++ = '\\';
                *ptr++ = '2';
                *ptr++ = 'a';
                break;
            case '(':
                *ptr++ = '\\';
                *ptr++ = '2';
                *ptr++ = '8';
                break;
            case ')':
                *ptr++ = '\\';
                *ptr++ = '2';
                *ptr++ = '9';
                break;
            case '\0':
                *ptr++ = '\\';
                *ptr++ = '0';
                *ptr++ = '0';
                break;
            default:
                *ptr++ = filter[i];
        }
    }
    *ptr = '\0';
    return escaped;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./Task68 <username> <domainComponent>\n");
        return 1;
    }

    char* username = argv[1];
    char* domainComponent = argv[2];

    char* safeUsername = escapeLDAPSearchFilter(username);
    char* safeDomainComponent = escapeLDAPSearchFilter(domainComponent);

    char baseDN[256];
    snprintf(baseDN, sizeof(baseDN), "dc=%s,dc=com", safeDomainComponent);
    char filter[256];
    snprintf(filter, sizeof(filter), "(cn=%s)", safeUsername);

    LDAP* ld;
    int rc;
    LDAPMessage* msg;
    char* dn;

    // Connect to LDAP server
    ld = ldap_init("localhost", 389);
    if (ld == NULL) {
        fprintf(stderr, "LDAP Error: Unable to initialize LDAP connection\n");
        return 1;
    }

    // Perform search
    rc = ldap_search_ext_s(ld, baseDN, LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, NULL, NULL, 0, &msg);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "LDAP Error: %s\n", ldap_err2string(rc));
        ldap_unbind_s(ld);
        return 1;
    }

    // Process results
    for (msg = ldap_first_message(ld, msg); msg != NULL; msg = ldap_next_message(ld, msg)) {
        if (ldap_get_msgtype(msg) == LDAP_RES_SEARCH_ENTRY) {
            BerElement* ber;
            char* attr, *val;
            for (ber = ldap_first_attribute(ld, msg, &dn); ber != NULL; ber = ldap_next_attribute(ld, msg, ber)) {
                attr = ldap_get_attribute_ber(ld, msg, ber);
                for (val = ldap_get_values_len(ld, msg, attr); val != NULL; val = ldap_get_values_len(ld, msg, attr)) {
                    printf("%s: %s\n", attr, val);
                }
                ldap_memfree(attr);
                ldap_memfree(val);
            }
            ldap_memfree(dn);
        }
    }

    ldap_msgfree(msg);
    ldap_unbind_s(ld);

    free(safeUsername);
    free(safeDomainComponent);

    return 0;
}