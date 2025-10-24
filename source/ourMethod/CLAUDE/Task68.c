
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ldap.h>
#include <ctype.h>

#define MAX_USERNAME_LEN 64
#define MAX_DC_LEN 253
#define MAX_FILTER_LEN 256
#define MAX_BASEDN_LEN 512
#define MAX_RESULT_LEN 4096

/* Validate username - alphanumeric, underscore, hyphen, dot only */
int validate_username(const char* username) {
    size_t len;
    size_t i;
    
    if (username == NULL) {
        return 0;
    }
    
    len = strlen(username);
    if (len == 0 || len > MAX_USERNAME_LEN) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        if (!isalnum((unsigned char)username[i]) && 
            username[i] != '.' && 
            username[i] != '_' && 
            username[i] != '-') {
            return 0;
        }
    }
    
    return 1;
}

/* Validate domain component */
int validate_dc(const char* dc) {
    size_t len;
    size_t i;
    int dot_count = 0;
    int component_len = 0;
    
    if (dc == NULL) {
        return 0;
    }
    
    len = strlen(dc);
    if (len == 0 || len > MAX_DC_LEN) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        if (dc[i] == '.') {
            if (component_len == 0 || component_len > 63) {
                return 0;
            }
            component_len = 0;
            dot_count++;
        } else if (isalnum((unsigned char)dc[i]) || dc[i] == '-') {
            component_len++;
        } else {
            return 0;
        }
    }
    
    /* Check last component */
    if (component_len == 0 || component_len > 63) {
        return 0;
    }
    
    return 1;
}
/* Escape LDAP special characters to prevent injection */
char* escape_ldap_string(const char* input) {
    size_t i;
    size_t j = 0;
    size_t input_len;
    char* escaped = NULL;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);

    /* Allocate maximum possible size (each char could be escaped) */
    escaped = (char*)calloc(input_len * 2 + 1, sizeof(char));
    if (escaped == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        switch (input[i]) {
            case '*':
            case '(':
            case ')':
            case '\\':
            case '\0':
                escaped[j++] = '\\';
                escaped[j++] = input[i];
                break;
            default:
                escaped[j++] = input[i];
                break;
        }
    }

    escaped[j] = '\0';
    return escaped;
}

/* Convert domain to LDAP base DN format */
char* domain_to_base_dn(const char* domain) {
    size_t i;
    size_t domain_len;
    size_t start = 0;
    char* base_dn = NULL;
    char* escaped_component = NULL;
    char component[64];
    int first = 1;
    size_t base_dn_pos = 0;

    if (domain == NULL) {
        return NULL;
    }

    domain_len = strlen(domain);
    base_dn = (char*)calloc(MAX_BASEDN_LEN, sizeof(char));
    if (base_dn == NULL) {
        return NULL;
    }

    for (i = 0; i <= domain_len; i++) {
        if (domain[i] == '.' || domain[i] == '\0') {
            size_t component_len = i - start;
            if (component_len >= sizeof(component)) {
                free(base_dn);
                return NULL;
            }

            memcpy(component, domain + start, component_len);
            component[component_len] = '\0';

            escaped_component = escape_ldap_string(component);
            if (escaped_component == NULL) {
                free(base_dn);
                return NULL;
            }

            if (!first) {
                if (base_dn_pos + 1 >= MAX_BASEDN_LEN) {
                    free(escaped_component);
                    free(base_dn);
                    return NULL;
                }
                base_dn[base_dn_pos++] = ',';
            }

            /* Check bounds before copying */
            if (base_dn_pos + 3 + strlen(escaped_component) >= MAX_BASEDN_LEN) {
                free(escaped_component);
                free(base_dn);
                return NULL;
            }

            memcpy(base_dn + base_dn_pos, "dc=", 3);
            base_dn_pos += 3;
            strcpy(base_dn + base_dn_pos, escaped_component);
            base_dn_pos += strlen(escaped_component);

            free(escaped_component);
            escaped_component = NULL;
            first = 0;
            start = i + 1;
        }
    }

    base_dn[base_dn_pos] = '\0';
    return base_dn;
}

int ldap_simple_bind_s(LDAP * ld, void * p, void * p1);

/* Search LDAP and return user information */
char* search_ldap(const char* username, const char* dc) {
    LDAP* ld = NULL;
    int result;
    int version = LDAP_VERSION3;
    char* base_dn = NULL;
    char* escaped_username = NULL;
    char filter[MAX_FILTER_LEN];
    char* attrs[] = {"uid", "cn", "mail", "displayName", NULL};
    LDAPMessage* search_result = NULL;
    LDAPMessage* entry = NULL;
    char* user_info = NULL;
    struct timeval timeout;
    char* dn = NULL;
    BerElement* ber = NULL;
    char* attr = NULL;
    struct berval** vals = NULL;
    size_t user_info_pos = 0;
    int i;

    /* Validate inputs */
    if (!validate_username(username)) {
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Invalid username format", 255);
        }
        return user_info;
    }

    if (!validate_dc(dc)) {
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Invalid domain component format", 255);
        }
        return user_info;
    }

    /* Initialize LDAP connection */
    result = ldap_initialize(&ld, "ldap://localhost:389");
    if (result != LDAP_SUCCESS) {
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Failed to initialize LDAP connection", 255);
        }
        return user_info;
    }

    /* Set LDAP version */
    result = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);
    if (result != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Failed to set LDAP protocol version", 255);
        }
        return user_info;
    }

    /* Set timeout */
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    ldap_set_option(ld, LDAP_OPT_NETWORK_TIMEOUT, &timeout);

    /* Anonymous bind */
    result = ldap_simple_bind_s(ld, NULL, NULL);
    if (result != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: LDAP bind failed", 255);
        }
        return user_info;
    }

    /* Construct base DN */
    base_dn = domain_to_base_dn(dc);
    if (base_dn == NULL) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Failed to construct base DN", 255);
        }
        return user_info;
    }

    /* Construct LDAP filter with escaped username */
    escaped_username = escape_ldap_string(username);
    if (escaped_username == NULL) {
        free(base_dn);
        ldap_unbind_ext_s(ld, NULL, NULL);
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Failed to escape username", 255);
        }
        return user_info;
    }

    /* Check filter length before construction */
    if (strlen(escaped_username) + 7 >= MAX_FILTER_LEN) {
        free(escaped_username);
        free(base_dn);
        ldap_unbind_ext_s(ld, NULL, NULL);
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: Username too long", 255);
        }
        return user_info;
    }

    snprintf(filter, MAX_FILTER_LEN, "(uid=%s)", escaped_username);
    free(escaped_username);
    escaped_username = NULL;

    /* Perform LDAP search */
    result = ldap_search_ext_s(
        ld,
        base_dn,
        LDAP_SCOPE_SUBTREE,
        filter,
        attrs,
        0,
        NULL,
        NULL,
        &timeout,
        1000,
        &search_result
    );

    free(base_dn);
    base_dn = NULL;

    if (result != LDAP_SUCCESS) {
        if (search_result != NULL) {
            ldap_msgfree(search_result);
        }
        ldap_unbind_ext_s(ld, NULL, NULL);
        user_info = (char*)calloc(256, sizeof(char));
        if (user_info != NULL) {
            strncpy(user_info, "Error: LDAP search failed", 255);
        }
        return user_info;
    }

    /* Allocate result buffer */
    user_info = (char*)calloc(MAX_RESULT_LEN, sizeof(char));
    if (user_info == NULL) {
        ldap_msgfree(search_result);
        ldap_unbind_ext_s(ld, NULL, NULL);
        return NULL;
    }

    /* Check if any entries found */
    if (ldap_count_entries(ld, search_result) == 0) {
        strncpy(user_info, "No user found", MAX_RESULT_LEN - 1);
        ldap_msgfree(search_result);
        ldap_unbind_ext_s(ld, NULL, NULL);
        return user_info;
    }

    /* Process first entry */
    entry = ldap_first_entry(ld, search_result);
    if (entry != NULL) {
        dn = ldap_get_dn(ld, entry);
        if (dn != NULL) {
            int len = snprintf(
                user_info + user_info_pos,
                MAX_RESULT_LEN - user_info_pos,
                "DN: %s\n",
                dn
            );
            if (len > 0 && (size_t)len < MAX_RESULT_LEN - user_info_pos) {
                user_info_pos += len;
            }
            ldap_memfree(dn);
        }

        /* Iterate through attributes */
        attr = ldap_first_attribute(ld, entry, &ber);
        while (attr != NULL && user_info_pos < MAX_RESULT_LEN - 100) {
            vals = ldap_get_values_len(ld, entry, attr);
            if (vals != NULL) {
                for (i = 0; vals[i] != NULL && user_info_pos < MAX_RESULT_LEN - 100; i++) {
                    int len = snprintf(
                        user_info + user_info_pos,
                        MAX_RESULT_LEN - user_info_pos,
                        "%s: %.*s\n",
                        attr,
                        (int)vals[i]->bv_len,
                        vals[i]->bv_val
                    );
                    if (len > 0 && (size_t)len < MAX_RESULT_LEN - user_info_pos) {
                        user_info_pos += len;
                    }
                }
                ldap_value_free_len(vals);
            }
            ldap_memfree(attr);
            attr = ldap_next_attribute(ld, entry, ber);
        }

        if (ber != NULL) {
            ber_free(ber, 0);
        }
    }

    user_info[MAX_RESULT_LEN - 1] = '\0';
    ldap_msgfree(search_result);
    ldap_unbind_ext_s(ld, NULL, NULL);

    return user_info;
}


int main(int argc, char* argv[]) {
    const char* test_usernames[] = {"testuser1", "john.doe", "admin", "user_123", "validuser"};
    const char* test_dcs[] = {"example.com", "corp.example.com", "test.local", "domain.org", "sub.domain.net"};
    int i;
    char* result = NULL;
    
    if (argc == 3) {
        /* Use command line arguments */
        result = search_ldap(argv[1], argv[2]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    } else {
        /* Run test cases */
        printf("Running test cases...\n");
        for (i = 0; i < 5; i++) {
            printf("\n--- Testing username: %s, dc: %s ---\n",
                   test_usernames[i], test_dcs[i]);
            result = search_ldap(test_usernames[i], test_dcs[i]);
            if (result != NULL) {
                printf("%s\n", result);
                free(result);
                result = NULL;
            }
        }
    }
    
    return 0;
}
