
#include <stdio.h>
#include <string.h>
#include <ctype.h>

long largest_series_product(const char* input, int span) {
    int len = strlen(input);
    if (span > len || span < 0) return -1;
    if (span == 0) return 1;
    
    long max_product = 0;
    
    for (int i = 0; i <= len - span; i++) {
        long product = 1;
        for (int j = 0; j < span; j++) {
            if (!isdigit(input[i + j])) return -1;
            product *= (input[i + j] - '0');
        }
        if (product > max_product) {
            max_product = product;
        }
    }
    return max_product;
}

int main() {
    printf("%ld\\n", largest_series_product("63915", 3));  // 162
    printf("%ld\\n", largest_series_product("1027839564", 3));  // 270
    printf("%ld\\n", largest_series_product("0123456789", 2));  // 72
    printf("%ld\\n", largest_series_product("12345", 6));  // -1
    printf("%ld\\n", largest_series_product("54321", 0));  // 1
    return 0;
}
