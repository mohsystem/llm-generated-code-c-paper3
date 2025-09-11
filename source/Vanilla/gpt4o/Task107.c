#include <stdio.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} JndiResource;

char* performJndiLookup(const char* jndiName) {
    JndiResource resources[] = {
        {"java:comp/env/jdbc/myDataSource", "DataSourceObject"},
        {"java:comp/env/jms/myQueue", "QueueObject"},
        {"java:comp/env/ejb/myBean", "BeanObject"},
        {"java:comp/env/mail/myMailSession", "MailSessionObject"},
        {"java:comp/env/url/myURL", "UrlObject"}
    };
    
    for (int i = 0; i < sizeof(resources) / sizeof(resources[0]); i++) {
        if (strcmp(resources[i].key, jndiName) == 0) {
            return resources[i].value;
        }
    }
    return "ResourceNotFound";
}

int main() {
    // Test cases
    const char* jndiNames[] = {
        "java:comp/env/jdbc/myDataSource",
        "java:comp/env/jms/myQueue",
        "java:comp/env/ejb/myBean",
        "java:comp/env/mail/myMailSession",
        "java:comp/env/url/myURL"
    };

    for (int i = 0; i < sizeof(jndiNames) / sizeof(jndiNames[0]); i++) {
        printf("Lookup result for %s: %s\n", jndiNames[i], performJndiLookup(jndiNames[i]));
    }

    return 0;
}