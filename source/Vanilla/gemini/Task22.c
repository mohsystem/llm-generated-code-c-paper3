#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Note: This C solution requires a slightly modified approach due to the limitations of C's type system
// compared to the other languages. It works with strings and converts valid integer strings to integers.

int is_integer_string(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1;
}



int *filter_list(char **list, int size, int *filtered_size) {
    int *filtered_list = malloc(size * sizeof(int)); // Allocate maximum possible size
    *filtered_size = 0;

    for (int i = 0; i < size; i++) {
        if (is_integer_string(list[i])) {
            filtered_list[*filtered_size] = atoi(list[i]);
            (*filtered_size)++;
        }
    }

    // Reallocate to the actual size used
    filtered_list = realloc(filtered_list, (*filtered_size) * sizeof(int));
    return filtered_list;
}


int main() {

    char *test1[] = {"1", "2", "a", "b"};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int filtered_size1;
    int *result1 = filter_list(test1, size1, &filtered_size1);
    for (int i = 0; i < filtered_size1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");
    free(result1);


     char *test2[] = {"1", "a", "b", "0", "15"};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int filtered_size2;
    int *result2 = filter_list(test2, size2, &filtered_size2);
    for (int i = 0; i < filtered_size2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
    free(result2);


      char *test3[] = {"1", "2", "a", "b", "aasf", "1", "123", "123"};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int filtered_size3;
    int *result3 = filter_list(test3, size3, &filtered_size3);
    for (int i = 0; i < filtered_size3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");
    free(result3);


     char *test4[] = {"1", "2", "3", "4", "5"};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int filtered_size4;
    int *result4= filter_list(test4, size4, &filtered_size4);
    for (int i = 0; i < filtered_size4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n");
    free(result4);


     char *test5[] = {"a", "b", "c", "d"};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    int filtered_size5;
    int *result5 = filter_list(test5, size5, &filtered_size5);
    for (int i = 0; i < filtered_size5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n");
    free(result5);

    return 0;
}