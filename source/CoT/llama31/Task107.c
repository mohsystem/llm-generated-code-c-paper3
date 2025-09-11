// JNDI is not available in C, so this is a placeholder
#include <stdio.h>
#include <string.h>

void lookup(const char* name) {
    // Mock implementation, as JNDI is not available in C
    printf("Mock lookup result for %s\n", name);
}

int main() {
    const char* names[] = {"java:comp/env/jdbc/datasource", "java:comp/env/myObject", "java:comp/env/anotherResource"};
    for (int i = 0; i < 3; i++) {
        lookup(names[i]);
    }
    return 0;
}