// Note: C does not have built-in support for Base64 decoding or JSON parsing.
// You would need to implement these functionalities manually or use external libraries.
// Here is a simplified example using only standard C libraries, but it lacks the actual decoding and parsing.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processRequest(const char* raw_data) {
    // This is a very simplified example and does not include actual Base64 decoding or JSON parsing.
    printf("Raw Data: %s\n", raw_data);
}

int main() {
    // Test cases
    const char* test_cases[] = {
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIjoiMjMwfQ==",
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIjoiMjMwfQ==",
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIjoiMjMwfQ==",
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIjoiMjMwfQ==",
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaGFuIjoiMjMwfQ=="
    };

    for (int i = 0; i < 5; i++) {
        processRequest(test_cases[i]);
    }

    return 0;
}